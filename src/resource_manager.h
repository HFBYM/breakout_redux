#pragma once
#include <map>
#include <memory>
#include"texture.h"
#include"shader.h"
#include<string>

/// @brief manager the shaders and textures and is a static class
class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager()
	{
		textures.clear();
		shaders.clear();
	}
	std::map<std::string, std::unique_ptr<Texture2D>> textures;
	std::map<std::string, std::unique_ptr<Shader>> shaders;

	/// @brief load texture2D from file
	/// @param file filepath
	/// @param has_alpha decides whether or not this texture has alpha channel
	/// @param name the texture name
	void loadTexture(const std::string &file, bool has_alpha, const std::string &name);

	void loadShader(const std::string &file, const std::string &name);

public:
	static std::string readFile(const std::string &file);

	const Shader &getShader(const std::string &name);
	const Texture2D &getTexture(const std::string &name);

	static ResourceManager &instance()
	{
		static ResourceManager instance;
		return instance;
	}
};