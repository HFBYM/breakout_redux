/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-22 20:55:46
 * @FilePath: \breakout_redux\src\game\level.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include "utils/pch.h"
namespace level
{
	class Level
	{
	public:
		/// @param path text file with level data
		Level(const std::string &path, unsigned int levelWidth, unsigned int levelHeight);
		~Level();

		void log_renderer();
		void detach_renderer();
		void log_collision();
		void detach_collision();
		void log_all();
		void detach_all();
		bool isCompleted() const;

	private:
		struct LevelData;
		std::unique_ptr<LevelData> data;
	};
} // namespace level
