#include"game.h"
#include<glad.h>	//the glew lib is 32bit so we use glad
#include<glfw3.h>	//this lib shuld be included after glad
#include<iostream>
#include"keyboard.h"
#include"resource_manager.h"
//#include"Debug.h"
#define CHECK_INIT() if(!isInit){\
	std::cout<<"ERROR::RESOURCE: "<<__FUNCTION__<<" operate game not initialized"<<std::endl;\
	__debugbreak();}


/// @brief the width and height of the window
static int init_screen_width = 800;
static int init_screen_height = 600;
static int screen_width;
static int screen_height;
static bool isInit = false;

static GLFWwindow* window = nullptr;

static GLFWwindow* gl_init()
{
	//initialize the glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					//version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//core module

	//create the window hint and check
	GLFWwindow* window = glfwCreateWindow(init_screen_width, init_screen_height, 
		"Breakout", nullptr, nullptr);
	if (!window)
	{
		std::cout << "ERROR::WINDOW: fail to create the window" << std::endl;
		glfwTerminate();
		__debugbreak();
	}

	//make this window the current context
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	//glad初始化方式与glew不一样
	{
		std::cout << "ERROR::GLAD: faid to initialize glad" << std::endl;
		glfwTerminate();
		__debugbreak();
	}
	//Check();
	return window;
}

/// @brief save the width and height resized
static void size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	screen_height = height;
	screen_width = width;
}

Game& Game:: get_instance()
{
	static Game m_game;
	return m_game;
}

void Game::init()
{
	isInit = true;

	window = gl_init();

	//set the viewport leftdown is origin
	glViewport(0, 0, init_screen_width, init_screen_height);	

	//function will work whenever keys pressed
	glfwSetKeyCallback(window, KeyBoard::key_callback);		

	//function will work each time window resized
	glfwSetWindowSizeCallback(window, size_callback);

	// to reduce the cost
	glEnable(GL_CULL_FACE);

	// enable blend and caution not to test the depth
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ResourceManager::init();

	std::cout << "Game is initialized" << std::endl;
}

void Game::run()
{
	CHECK_INIT();
	std::cout << "Game is running" << std::endl;
}

Game::~Game()
{
	ResourceManager::clear();
	std::cout << "Game is deleted" << std::endl;
}
