#include "level.h"
#include "Resource_manager.h"
#include <iostream>

static void load(const mString &path, std::vector<std::vector<unsigned int>> &tileData)
{
	mString file = ResourceManager::readFile(path);

	std::vector<unsigned int> row;
	char c = NULL;
	for (unsigned int i = 0; i < file.getSize(); i++)
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
		row.push_back(c - 48);
	}
	if (tileData.size() <= 1)
		throw std::runtime_error("ERROR::LEVEL: loading file ");
}

Level::Level(unsigned int id, const mString &path, unsigned int levelWidth, unsigned int levelHeight)
{
	std::vector<std::vector<unsigned int>> tileData;
	try
	{
		load(path, tileData);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << path.getStr() << " has wrong data" << std::endl;
	}
	// get the number of lives in the last line
	this->lives = tileData[tileData.size() - 1][0];

	// get rid of it in the bricks
	tileData.pop_back();

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
			if (tileData[y][x] == Brick::SOLID)
			{
				this->bricks.push_back(std::make_unique<Brick>(pos, size, "block_solid", Brick::SOLID, true, glm::vec3(0.8f, 0.8f, 0.7f)));
			}
			else if (tileData[y][x] == Brick::NONE)
				continue;
			else
			{
				glm::vec3 color(1.0f);
				try
				{
					switch (tileData[y][x])
					{
					case Brick::BLUE:
						color = glm::vec3(0.2f, 0.6f, 1.0f);
						break;
					case Brick::GREEN:
						color = glm::vec3(0.0f, 0.7f, 0.0f);
						break;
					case Brick::YELLOW:
						color = glm::vec3(0.8f, 0.8f, 0.4f);
						break;
					case Brick::RED:
						color = glm::vec3(1.0f, 0.5f, 0.0f);
						break;
					default:
						throw std::runtime_error("ERROR::LEVEL: category of brick is wrong");
					}
				}
				catch (std::exception &e)
				{
					std::cerr << e.what() << std::endl;
					std::cerr << "unnamed type of brick in " << path.getStr() << std::endl;
					color = glm::vec4(1.0f);
				}
				this->bricks.push_back(std::make_unique<Brick>(pos, size, "block", static_cast<Brick::BrickType>(tileData[y][x]), false, color));
			}
		}
	}
}

void Level::log_renderer()
{
	for (auto &i : bricks)
		i->log_renderer();
}

void Level::detach_renderer()
{
	for (auto &i : bricks)
		i->detach_renderer();
}

void Level::log_collision()
{
	for (auto &i : bricks)
		i->log_collision();
}

void Level::detach_collision()
{
	for (auto &i : bricks)
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

void Level::Rotate()
{
	for (auto &i : bricks)
	{
		i->Rotate();
	}
}
