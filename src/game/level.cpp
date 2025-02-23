/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:50:39
 * @FilePath: \breakout_redux\src\game\level.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "game/level.h"

#include <iostream>
#include <vector>
#include<string>

#include "objects/Brick.h"
#include "resource_manage/resource_manager.h"

namespace level
{
	struct Level::LevelData
	{
		std::vector<std::unique_ptr<brick:: Brick>> bricks;
	};
	namespace
	{
		/// @brief load the brick data from .level file
		/// @param path the path of the .level file
		/// @return 2D arrays of unsigned int
		std::vector<std::vector<unsigned int>> load(const std::string &path)
		{
			using resource_manager::ResourceManager;
			std::string file = ResourceManager::instance().readFile(path);
			constexpr unsigned int diff_from_char_to_num = 48;
			std::vector<std::vector<unsigned int>> tileData;
			char c = NULL;
			std::vector<unsigned int> row;
			for (unsigned int i = 0; i < file.size(); i++)
			{
				c = file[i];
				if (isspace(c))
				{
					if (c == '\n')
					{
						tileData.push_back(row);
						row.clear();
					}
					continue;
				}
				row.push_back(static_cast<unsigned int>(c) - diff_from_char_to_num);
			}
			if (tileData.size() <= 1)
				throw std::runtime_error("ERROR::LEVEL: loading file ");
			return tileData;
		}
	} // namespace

	Level::Level(const std::string &path, unsigned int levelWidth, unsigned int levelHeight)
	: data(std::make_unique<LevelData>())
	{
		auto tileData = load(path);
		using brick::Brick;
		// calculate the param
		unsigned int num_in_height = static_cast<unsigned int>(tileData.size());
		unsigned int num_in_width = static_cast<unsigned int>(tileData[0].size());
		float unit_width = (levelWidth / static_cast<float>(num_in_width));
		float unit_height = (levelHeight / static_cast<float>(num_in_height));

		for (unsigned int y = 0; y < num_in_height; y++)
		{
			for (unsigned int x = 0; x < num_in_width; x++)
			{
				// the leftup is origin
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				if (tileData[y][x] == static_cast<unsigned int>(Brick::BrickType::SOLID))
				{
					data->bricks.push_back(std::make_unique<Brick>(pos, size, "block_solid",
						Brick::BrickType::SOLID, true, glm::vec3(0.8f, 0.8f, 0.7f)));
				}
				else if (tileData[y][x] == static_cast<unsigned int>(Brick::BrickType::NONE))
					continue;
				else
				{
					glm::vec3 color(1.0f);
					try
					{
						switch (static_cast<Brick::BrickType>(tileData[y][x]))
						{
						case Brick::BrickType::BLUE:
							color = glm::vec3(0.2f, 0.6f, 1.0f);
							break;
						case Brick::BrickType::GREEN:
							color = glm::vec3(0.0f, 0.7f, 0.0f);
							break;
						case Brick::BrickType::YELLOW:
							color = glm::vec3(0.8f, 0.8f, 0.4f);
							break;
						case Brick::BrickType::RED:
							color = glm::vec3(1.0f, 0.5f, 0.0f);
							break;
						default:
							throw std::runtime_error("ERROR::LEVEL: category of brick is wrong");
						}
					}
					catch (std::exception &e)
					{
						std::cerr << e.what() << std::endl;
						std::cerr << "unnamed type of brick in " << path << std::endl;
						color = glm::vec4(1.0f);
					}
					data->bricks.push_back(std::make_unique<Brick>(pos, size, "block",
						static_cast<Brick::BrickType>(tileData[y][x]), false, color));
				}
			}
		}
		log_all();
	}

    Level::~Level()
    {
		detach_all();
    }
    void Level::log_renderer()
    {
		for (auto &i : data->bricks)
			i->log_renderer();
	}

	void Level::detach_renderer()
	{
		for (auto &i : data->bricks)
			i->detach_renderer();
	}

	void Level::log_collision()
	{
		for (auto &i : data->bricks)
			i->log_collision();
	}

	void Level::detach_collision()
	{
		for (auto &i : data->bricks)
			i->detach_collision();
	}

	void Level::log_all()
	{
		log_renderer();
		log_collision();
	}

	void Level::detach_all()
	{
		detach_renderer();
		detach_collision();
	}

	bool Level::isCompleted() const
	{
		for (auto &brick : data->bricks)
		{
			if (brick->checkSolid())
				continue;
			if (!brick->isDestroyed())
				return false;
		}
		return true;
	}
} // namespace level
