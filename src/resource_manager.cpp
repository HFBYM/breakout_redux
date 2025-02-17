#include "resource_manager.h"
#include <fstream>
#include <sstream>
#include <stb.image.h>
#include <map>
#include <glad.h>
#include <string>
#include <memory>
#include <iostream>
#include "debug.h"
#include <json.hpp>
#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif
using json = nlohmann::json;
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
	shaders[name] = std::make_unique<Shader>(name, ss[static_cast<int>(Type::VERTEX)].str().c_str(), ss[static_cast<int>(Type::FRAGMENT)].str().c_str());
}

void ResourceManager::loadTexture(const std::string &file, bool has_alpha, const std::string &name)
{

	// usually we need to turn up and down the texture cause OpenGL renders from the leftdown while
	// picture loaded from leftup. But it isn't here because the proj matrix has already turned
	// stbi_set_flip_vertically_on_load(1);

	int width, height;
	auto channel = has_alpha ? GL_RGBA : GL_RGB;

	// the forth parm returns the channels of the image which is of no use
	unsigned char *image = stbi_load(file.c_str(), &width, &height, 0, has_alpha ? 4 : 3);

	textures[name] = std::make_unique<Texture2D>(name, channel, channel, width, height, image);

	// the data in CPU is useless after sended to GPU
	stbi_image_free(image);
}

ResourceManager::ResourceManager()
{
	std::ifstream file(PROJECT_DIR "/src/resource_loading.json");
	json data = json::parse(file);
	std::string project_dir(PROJECT_DIR "/");

	// load in shaders
	for (auto &i : data["resources"]["shaders"])
		loadShader(project_dir + i["path"].get<std::string>(), i["name"].get<std::string>());

	// load in textures
	for (auto &i : data["resources"]["textures"])
		loadTexture(project_dir + i["path"].get<std::string>(), i["has_alpha"].get<bool>(), i["name"].get<std::string>());
}

const Shader &ResourceManager::getShader(const std::string &name)
{
	try
	{
		if (shaders.find(name) == shaders.end())
			throw std::runtime_error("ERROR::GET_SHADER: shader not found");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "name: " << name << std::endl;
		MDEBUG();
	}
	return *shaders[name];
}
const Texture2D &ResourceManager::getTexture(const std::string &name)
{
	try
	{
		if (textures.find(name) == textures.end())
			throw std::runtime_error("ERROR::GET_TEXTURE: texture not found");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "name: " << name << std::endl;
		MDEBUG();
	}
	return *textures[name];
}
std::string ResourceManager::readFile(const std::string &file)
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
