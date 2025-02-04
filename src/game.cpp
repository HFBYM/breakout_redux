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
#include "player.h"
#include "movement.h"
#include "collision.h"
#include "ball.h"
#include "particle_generator.h"
#include "soundEngine.h"

/// @brief the width and height of the window
static int init_screen_width = 800;
static int init_screen_height = 600;
static int screen_width;
static int screen_height;

static GLFWwindow *window = nullptr;

static GLFWwindow *gl_init()
{
	// initialize the glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core module

	// create the window hint and check
	GLFWwindow *window = glfwCreateWindow(init_screen_width, init_screen_height, "Breakout", nullptr, nullptr);

	if (!window)
		throw std::runtime_error("ERROR::WINDOW: fail to create the window");
	// make this window the current context
	glfwMakeContextCurrent(window);

	// it's different from glew
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("ERROR::GLAD: faid to initialize glad");

	return window;
}

/// @brief save the width and height resized
static void size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	screen_height = height;
	screen_width = width;
}

Game::Game()
{
	try{
		window = gl_init();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// set the viewport leftdown is origin
	glViewport(0, 0, init_screen_width, init_screen_height);

	auto func = [](GLFWwindow *window, int key, int scancode, int action, int mods)
	{ KeyBoard::instance().key_callback(window, key, scancode, action, mods); };

	// function will work whenever keys pressed
	// glfwSetKeyCallback(window, KeyBoard::key_callback);
	glfwSetKeyCallback(window, func);

	// function will work each time window resized
	glfwSetWindowSizeCallback(window, size_callback);

	// to reduce the cost
	glEnable(GL_CULL_FACE);

	// enable blend and caution not to test the depth
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	level = std::make_unique<Level>(0, PROJECT_DIR "/assets/levels/level_1.lvl", init_screen_width, init_screen_height / 2);
	level->log_all();

	player = std::make_unique<Player>(init_screen_width, init_screen_height);
	player->log_all();

	ball = std::make_unique<Ball>(init_screen_width, init_screen_height);
	ball->log_all();
	ball->setPos(player->getPos(), player->getSize());

	SoundEngine::instance().play_music(SoundEngine::Song::BGM);
}

void Game::run()
{
	// use frame time to make it smooth
	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	// 60hz it will change the time the loop spend
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		// calculate frame time
		GLfloat currentTime = (GLfloat)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// trigger the events such as mouse and keyboard
		glfwPollEvents();

		ball->setPos(player->getPos(), player->getSize());
		level->Rotate();
		ParticleGenerator::instance().update(deltaTime);

		Renderer::instance().render(init_screen_width, init_screen_height);

		Movement::instance().move(deltaTime);
		Collision::instance().collision(deltaTime);

		// swap the two buffers
		glfwSwapBuffers(window);
	}
}

Game::~Game()
{
	glfwTerminate();
}
