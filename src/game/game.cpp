/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 16:29:05
 * @FilePath: \breakout_redux\src\game\game.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "game/game.h"

#ifdef _WIN32
#include <windows.h>
#include <imm.h>
#else
#error "not windows"
#endif

#include <glad.h>
#include <glfw3.h>	//this should be included after glad.h

#include "utils/pch.h"
#include "obj_for_engines/renderObj.h"
#include "resource_manage/resource_manager.h"
#include "engines/keyboard.h"
#include "engines/renderer.h"
#include "engines/movement.h"
#include "engines/collision.h"
#include "engines/particle_generator.h"
#include "engines/soundEngine.h"
#include "game/player.h"
#include "game/menu.h"
#include "game/level.h"

#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif

namespace game
{
	using keyboard::KeyBoard;
	using level::Level;
	using menu::Menu;
	using movement::Movement;
	using particle_generator::ParticleGenerator;
	using player::Player;
	using render::Renderer;
	using render_obj::RenderObj;
	using sound_engine::SoundEngine;
	using collision::Collision;
	struct Game::GameData
	{
		GLFWwindow *window = nullptr;
		int monitor_width, monitor_height = 0;

		/// @brief the width and height of the window
		unsigned int init_screen_height = 600;
		unsigned int init_screen_width = 800;

		std::unique_ptr<Level> level = nullptr;
		std::unique_ptr<RenderObj> background = nullptr;
		std::unique_ptr<Menu> menu = nullptr;
		std::vector<std::unique_ptr<Player>> players;
	};

	Game::Game() : game_data(std::make_unique<GameData>())
	{
		try
		{
			// initialize
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.3
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core module

			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			// create the window hint and check
			game_data->window = glfwCreateWindow(game_data->init_screen_width,
												 game_data->init_screen_height, "Breakout", nullptr, nullptr);

			if (!game_data->window)
				throw std::runtime_error("ERROR::WINDOW: fail to create the window");

			glfwMakeContextCurrent(game_data->window);

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

		// set the window pos
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		if (monitor)
			glfwGetMonitorWorkarea(monitor, NULL, NULL,
								   &game_data->monitor_width, &game_data->monitor_height);
		else
			std::cerr << "ERROR::GLFW: fail to get the monitor" << std::endl;
		glfwSetWindowPos(game_data->window,
						 (game_data->monitor_width - game_data->init_screen_width) / 2,
						 (game_data->monitor_height - game_data->init_screen_height) / 2);

		glViewport(0, 0, game_data->init_screen_width, game_data->init_screen_height);

		auto key_callback =
			[](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			KeyBoard::instance().key_callback(window, key, scancode, action, mods);
		};

		glfwSetKeyCallback(game_data->window, key_callback);

		// to reduce the cost
		glEnable(GL_CULL_FACE);

		// enable blend and caution not to test the depth
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// 60hz it will change the time the loop spend
		glfwSwapInterval(1);

		auto game_callback = [this](int start_menu_choice, int level_choice)
		{
			this->onGame(start_menu_choice, level_choice);
		};

		game_data->menu = std::make_unique<Menu>(game_callback);

		game_data->background =
			std::make_unique<RenderObj>("Background", glm::vec2(0.0f),
										glm::vec2(game_data->init_screen_width, game_data->init_screen_height),
										"background", "sprite", glm::vec4(1.0f));
		game_data->background->log_renderer();

		SoundEngine::instance().play_music("BGM");
	}

	void Game::run()
	{
		game_data->menu->run();
	}

	Game::~Game()
	{
		glfwTerminate();
	}

	void Game::onGame(int start_menu_choice, int level_choice)
	{
		game_data->players.clear();
		float time = 0.0f;
		if (start_menu_choice == 0)
		{
			time = static_cast<float>(glfwGetTime());
			game_data->players.push_back(std::make_unique<Player>(game_data->init_screen_width,
																  game_data->init_screen_height, Player::PlayerID::Player_Single));
		}
		else if (start_menu_choice == 1)
		{
			game_data->players.push_back(std::make_unique<Player>(game_data->init_screen_width,
																  game_data->init_screen_height, Player::PlayerID::Player1));
			game_data->players.push_back(std::make_unique<Player>(game_data->init_screen_width,
																  game_data->init_screen_height, Player::PlayerID::Player2));
		}
		else
			return;
		for (auto &player : game_data->players)
			player->log();

		std::string level_path(PROJECT_DIR "/assets/levels/level_");
		level_path += (static_cast<char>(level_choice + 1 + 48));
		level_path.append(".lvl");

		game_data->level = std::make_unique<level::Level>(level_path, game_data->init_screen_width,
														  game_data->init_screen_height / 2);
		game_data->level->log_all();

		glfwShowWindow(game_data->window);
		glfwSetWindowShouldClose(game_data->window, GLFW_FALSE);

		// use frame time to make it smooth
		GLfloat deltaTime = 0.0f;
		GLfloat lastTime = 0.0f;

		while (!glfwWindowShouldClose(game_data->window))
		{
			// calculate frame time
			GLfloat currentTime = (GLfloat)glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// trigger the events such as mouse and keyboard
			glfwPollEvents();

			if (game_data->level->isCompleted())
				glfwSetWindowShouldClose(game_data->window, true);

			for (auto &player : game_data->players)
				player->update(deltaTime);

			ParticleGenerator::instance().update(deltaTime);

			Renderer::instance().render(game_data->init_screen_width,
										game_data->init_screen_height);

			Movement::instance().doMove(deltaTime);
			Collision::instance().collision(deltaTime);

			// swap the two buffers
			glfwSwapBuffers(game_data->window);
		}
		glfwHideWindow(game_data->window);
		if (start_menu_choice == 0)
		{
			time = static_cast<float>(glfwGetTime()) - time;
			std::cout << "time consumed: " << time << "seconds" << std::endl;
		}
	}
} // namespace game
