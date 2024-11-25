#include"game.h"
#include<glad.h>	//the glew lib is 32bit so we use glad
#include<glfw3.h>	//this lib shuld be included after glad
#include<iostream>
#include"Debug.h"

/// @brief the width and height of the window
static int init_screen_width = 800;
static int init_screen_height = 600;

static GLFWwindow* glInit()
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
	Check();
	return window;
}

Game::Game(){}
Game::~Game()
{
}

Game& Game:: get_instance()
{
	static Game m_game;
	return m_game;
}

void Game::init()
{

}

void Game::run()
{
}
