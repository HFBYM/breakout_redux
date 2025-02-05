#include "resource_manager.h"
#include <fstream>
#include <sstream>
#include <stb.image.h>
#include <map>
#include <glad.h>
#include "mString.h"
#include <memory>
#include <iostream>
#include"debug.h"
#ifndef PROJECT_DIR
#define PROJECT_DIR "."
#endif

void ResourceManager::loadShader(const mString &file, const mString &name)
{
	std::ifstream ifs(file.getStr());
	try
	{
		if (!ifs.is_open())
			throw std::runtime_error("ERROR::SHADER: file not found");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "failed to open " << name.getStr() << std::endl;
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
		std::cerr << "name: " << name.getStr() << " in\t" << file.getStr() << std::endl;
		return;
	}
	shaders[name] = std::make_unique<Shader>(name, ss[static_cast<int>(Type::VERTEX)].str().c_str(), ss[static_cast<int>(Type::FRAGMENT)].str().c_str());
}

void ResourceManager::loadTexture(const mString &file, bool has_alpha, const mString &name)
{

	// usually we need to turn up and down the texture cause OpenGL renders from the leftdown while
	// picture loaded from leftup. But it isn't here because the proj matrix has already turned
	// stbi_set_flip_vertically_on_load(1);

	int width, height;
	auto channel = has_alpha ? GL_RGBA : GL_RGB;

	// the forth parm returns the channels of the image which is of no use
	unsigned char *image = stbi_load(file.getStr(), &width, &height, 0, has_alpha ? 4 : 3);

	textures[name] = std::make_unique<Texture2D>(name, channel, channel, width, height, image);

	// the data in CPU is useless after sended to GPU
	stbi_image_free(image);
}

ResourceManager::ResourceManager()
{
	// TODOjson文件管理
	// load in shaders
	loadShader(PROJECT_DIR "/assets/shaders/postProcess.shader", "postProcess");
	loadShader(PROJECT_DIR "/assets/shaders/sprite.shader", "sprite");

	loadShader(PROJECT_DIR "/assets/shaders/particle.shader", "particle");
	// ResourceManager::getShader("particle").use().setInteger("sprite", 0);	//设定采样槽
	// ResourceManager::getShader("particle").use().setMatrix4("proj", proj);	//设置正射投影

	// load in textures
	loadTexture(PROJECT_DIR "/assets/textures/background.jpg", false, "background");
	loadTexture(PROJECT_DIR "/assets/textures/block.png", false, "block");
	loadTexture(PROJECT_DIR "/assets/textures/block_solid.png", false, "block_solid");
	loadTexture(PROJECT_DIR "/assets/textures/basketball.png", true, "basketball");
	loadTexture(PROJECT_DIR "/assets/textures/paddle.png", true, "paddle");

	loadTexture(PROJECT_DIR "/assets/textures/particle.png", true, "particle");

	loadTexture(PROJECT_DIR "/assets/textures/powerup_chaos.png", false, "tex_chaos");
	loadTexture(PROJECT_DIR "/assets/textures/powerup_confuse.png", false, "tex_confuse");
	loadTexture(PROJECT_DIR "/assets/textures/powerup_increase.png", false, "tex_size");
	loadTexture(PROJECT_DIR "/assets/textures/powerup_passthrough.png", false, "tex_pass");
	loadTexture(PROJECT_DIR "/assets/textures/powerup_speed.png", false, "tex_speed");
	loadTexture(PROJECT_DIR "/assets/textures/powerup_sticky.png", false, "tex_sticky");
}

const Shader &ResourceManager::getShader(const mString &name)
{
	try
	{
		if (shaders.find(name) == shaders.end())
			throw std::runtime_error("ERROR::GET_SHADER: shader not found");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "name: " << name.getStr() << std::endl;
		MDEBUG();
	}
	return *shaders[name];
}
const Texture2D &ResourceManager::getTexture(const mString &name)
{
	try
	{
		if (textures.find(name) == textures.end())
			throw std::runtime_error("ERROR::GET_TEXTURE: texture not found");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "name: " << name.getStr() << std::endl;
		MDEBUG();
	}
	return *textures[name];
}
mString ResourceManager::readFile(const mString &file)
{
	std::ifstream ifs(file.getStr());
	try{
		if (!ifs.is_open())
			throw std::runtime_error("ERROR::FILE: failed to open");
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "path: " << file.getStr() << std::endl;
		return NULL;
	}

	std::string line;
	std::stringstream ss;

	while (std::getline(ifs, line))
		ss << line << std::endl;

	return ss.str().c_str();
}
