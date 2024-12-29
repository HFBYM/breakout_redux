#pragma once
#include <map>
#include <memory>
class mString;
#include"texture.h"
#include"shader.h"

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
	std::map<mString, std::unique_ptr<Texture2D>> textures;
	std::map<mString, std::unique_ptr<Shader>> shaders;

	/// @brief load texture2D from file
	/// @param file filepath
	/// @param has_alpha decides whether or not this texture has alpha channel
	/// @param name the texture name
	void loadTexture(const mString &file, bool has_alpha, const mString &name);

	void loadShader(const mString &file, const mString &name);

public:
	static mString readFile(const mString &file);

	const Shader &getShader(const mString &name);
	const Texture2D &getTexture(const mString &name);

	static ResourceManager &instance()
	{
		static ResourceManager instance;
		return instance;
	}
};