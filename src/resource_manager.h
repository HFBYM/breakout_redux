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
	static void loadShader(const char* file, const char* name);

	/// @brief load texture2D from file
	/// @param file filepath
	/// @param has_alpha decides whether or not this texture has alpha channel
	/// @param name the texture name
	static void loadTexture(const char* file, bool has_alpha, const char* name);

	/// @brief clear all the shaders and textures when program terminated
	static void clear();
	
	static Shader& getShader(const char* name);
	static Texture2D& getTexture(const char* name);
private:
	static Texture2D loadTextureFromFile(const char* file, bool has_alpha);
};
