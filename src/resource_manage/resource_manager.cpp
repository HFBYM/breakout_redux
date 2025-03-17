/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:34:26
 * @FilePath: \breakout_redux\src\resource_manage\resource_manager.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "resource_manage/resource_manager.h"

#include <stb.image.h>
#include <glad.h>

#include <fstream>
#include <sstream>

#include <json.hpp>

#include "utils/debug.h"

#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif

namespace resource_manager
{
	struct ResourceManager::ResourceData
	{
		std::map<std::string, std::unique_ptr<texture::Texture2D>> textures;
		std::map<std::string, std::unique_ptr<shader::Shader>> shaders;
		json data_json;
	};
	void ResourceManager::loadShader(const std::string &file, const std::string &name)
	{
		std::ifstream ifs(file);
		try
		{
			if (!ifs.is_open())
				throw std::runtime_error("ERROR::SHADER: file not found");
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			std::cerr << "failed to open " << name << std::endl;
			return;
		}
		std::string line;
		std::stringstream ss[2];

		// use enum type for classification
		enum class Type
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1
		};
		Type type = Type::NONE;

		// record if anything is found
		bool v_found = false, f_found = false;
		while (std::getline(ifs, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = Type::VERTEX;
					v_found = true;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = Type::FRAGMENT;
					f_found = true;
				}
				// if the type is find just skip the turn cause it the "#shader" couldn't be compiled
				continue;
			}
			// remember the endl which shader needs but ignored by getline
			ss[static_cast<int>(type)] << line << std::endl;
		}
		try
		{
			if (!v_found)
				throw std::runtime_error("ERROR::SHADER: no vertex shader found");
			if (!f_found)
				throw std::runtime_error("ERROR::SHADER: no fragment shader found");
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			std::cerr << "name: " << name << " in\t" << file << std::endl;
			return;
		}
		data->shaders[name] = std::make_unique<Shader>(name,
													   ss[static_cast<int>(Type::VERTEX)].str(),
													   ss[static_cast<int>(Type::FRAGMENT)].str());
	}

	void ResourceManager::loadTexture(const std::string &file,
									  bool has_alpha, const std::string &name)
	{
		// usually we need to turn up and down the texture cause OpenGL
		// renders from the leftdown while picture loaded from leftup.
		// But it isn't here because the proj matrix has already turned
		// stbi_set_flip_vertically_on_load(1);

		int width, height;
		auto channel = has_alpha ? GL_RGBA : GL_RGB;

		// the forth parm returns the channels of the image which is of no use
		unsigned char *image = stbi_load(file.c_str(), &width, &height, 0, has_alpha ? 4 : 3);

		data->textures[name] = std::make_unique<Texture2D>(name, channel, channel,
														   width, height, image);

		// the data in CPU is useless after sended to GPU
		stbi_image_free(image);
	}

	ResourceManager::ResourceManager():data(std::make_unique<ResourceData>())
	{
		std::ifstream file(PROJECT_DIR "/src/resource_manage/resource_loading.json");
		// data->data_json = json::parse(file);
		data->data_json = json::parse(file);
		std::string project_dir(PROJECT_DIR "/");

		// load in shaders
		for (auto &[name, i] : data->data_json
								   ["resources"]["shaders"]
									   .get<std::map<std::string, json>>())
			loadShader(project_dir + i["path"].get<std::string>(), name);

		// load in textures
		for (auto &[name, i] : data->data_json
								   ["resources"]["textures"]
									   .get<std::map<std::string, json>>())
			loadTexture(project_dir + i["path"].get<std::string>(),
						i["has_alpha"].get<bool>(), name);
	}

	const ResourceManager::Shader &ResourceManager::getShader(const std::string &name) const
	{
		try
		{
			if (data->shaders.find(name) == data->shaders.end())
				throw std::runtime_error("ERROR::GET_SHADER: shader not found");
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			std::cerr << "name: " << name << std::endl;
			MDEBUG();
		}
		return *data->shaders[name];
	}
	const ResourceManager::Texture2D &ResourceManager::getTexture(
		const std::string &name) const
	{
		try
		{
			if (data->textures.find(name) == data->textures.end())
				throw std::runtime_error("ERROR::GET_TEXTURE: texture not found");
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			std::cerr << "name: " << name << std::endl;
			MDEBUG();
		}
		return *data->textures[name];
	}
	std::string ResourceManager::readFile(const std::string &file) const
	{
		std::ifstream ifs(file);
		try
		{
			if (!ifs.is_open())
				throw std::runtime_error("ERROR::FILE: failed to open");
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			std::cerr << "path: " << file << std::endl;
			return NULL;
		}

		std::string line;
		std::stringstream ss;

		while (std::getline(ifs, line))
			ss << line << std::endl;

		return ss.str().c_str();
	}
	ResourceManager::~ResourceManager()
	{
		data->textures.clear();
		data->shaders.clear();
	}
	const ResourceManager::json &ResourceManager::getJsonData() const
	{
		return data->data_json;
	}
} // namespace resource_manager
