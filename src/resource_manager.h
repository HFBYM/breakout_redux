#pragma once
class Shader;
class Texture2D;

/// @brief manager the shaders and textures and is a static class
class ResourceManager
{
private:
	ResourceManager() = default;
	~ResourceManager() = default;
public:
	static void init();

	/// @brief clear all the shaders and textures when program terminated
	static void clear();
	
	static Shader& getShader(const char* name);
	static Texture2D& getTexture(const char* name);
};
