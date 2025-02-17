#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif
#include "game.h"
#include <glad.h>  //the glew lib is 32bit so we use glad
#include <glfw3.h> //this lib shuld be included after glad
#include "keyboard.h"
#include "resource_manager.h"
#include "renderer.h"
#include "level.h"
#include "movement.h"
#include "collision.h"
#include "particle_generator.h"
#include "soundEngine.h"
#include "player.h"
#include "menu.h"
#ifdef _WIN32
#include <windows.h>
#include <imm.h>
#else
#error "not windows"
#endif

/// @brief the width and height of the window
static unsigned int init_screen_height = 600;
static unsigned int init_screen_width = 800;
static unsigned int screen_width;
static unsigned int screen_height;

/// @brief save the width and height resized
static void size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	screen_height = height;
	screen_width = width;
}

Game::Game()
{
	try
	{
		// initialize the glfw
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core module

		// hide the window when created
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		// disable the imput method editor
		//  glfwWindowHint(GLFW_IME)
		//  glfwSetCharCallback(window, nullptr);

		// create the window hint and check
		window = glfwCreateWindow(init_screen_width, init_screen_height, "Breakout", nullptr, nullptr);

		if (!window)
			throw std::runtime_error("ERROR::WINDOW: fail to create the window");

		// make this window the current context
		glfwMakeContextCurrent(window);

		// it's different from glew
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("ERROR::GLAD: faid to initialize glad");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// disable the imput method editor
	ImmDisableIME(GetCurrentThreadId());

	// set the viewport size
	glViewport(0, 0, init_screen_width, init_screen_height);

	auto key_callback = [](GLFWwindow *window, int key, int scancode, int action, int mods)
	{ KeyBoard::instance().key_callback(window, key, scancode, action, mods); };

	// function will work whenever keys pressed
	glfwSetKeyCallback(window, key_callback);

	// function will work each time window resized
	glfwSetWindowSizeCallback(window, size_callback);

	// to reduce the cost
	glEnable(GL_CULL_FACE);

	// enable blend and caution not to test the depth
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 60hz it will change the time the loop spend
	glfwSwapInterval(1);

	auto game_callback = [this](int start_menu_choice, int level_choice)
	{ this->onGame(start_menu_choice, level_choice); };

	menu = std::make_unique<Menu>(game_callback);

	background = std::make_unique<RenderObj>("Background", glm::vec2(0.0f), glm::vec2(init_screen_width, init_screen_height), "background", "sprite");
	background->log_renderer();

	SoundEngine::instance().play_music(SoundEngine::Song::BGM);
}

void Game::run()
{
	menu->run();
}

Game::~Game()
{
	glfwTerminate();
}

void Game::onGame(int start_menu_choice, int level_choice)
{
	players.clear();
	if (start_menu_choice == 0)
	{
		players.push_back(std::make_unique<Player>(init_screen_width, init_screen_height, Player::PlayerID::Player_Single));
	}
	else if (start_menu_choice == 1)
	{
		players.push_back(std::make_unique<Player>(init_screen_width, init_screen_height, Player::PlayerID::Player1));
		players.push_back(std::make_unique<Player>(init_screen_width, init_screen_height, Player::PlayerID::Player2));
	}
	for (auto &player : players)
		player->log_all();

	std::string level_path(PROJECT_DIR "/assets/levels/level_");
	level_path += ((char)(level_choice + 1 + 48));
	level_path.append(".lvl");

	level = std::make_unique<Level>(0, level_path, init_screen_width, init_screen_height / 2);
	level->log_all();

	glfwShowWindow(window);
	glfwSetWindowShouldClose(window, GLFW_FALSE);

	// use frame time to make it smooth
	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// calculate frame time
		GLfloat currentTime = (GLfloat)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// trigger the events such as mouse and keyboard
		glfwPollEvents();

		level->Rotate();
		for (auto &player : players)
			player->update(deltaTime);

		ParticleGenerator::instance().update(deltaTime);

		Renderer::instance().render(init_screen_width, init_screen_height);

		Movement::instance().move(deltaTime);
		Collision::instance().collision(deltaTime);

		// swap the two buffers
		glfwSwapBuffers(window);
	}
}
