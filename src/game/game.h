/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 16:24:20
 * @FilePath: \breakout_redux\src\game\game.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include <memory>
namespace game
{

	/// @brief singleton and all you need is to run
	class Game
	{
	public:
		static Game &get_instance()
		{
			static Game m_game;
			return m_game;
		}

		void run();

	private:
		Game();
		~Game();

		void onGame(int start_menu_choice, int level_choice);

		struct GameData;
		std::unique_ptr<GameData> game_data;
	};
} // namespace game
