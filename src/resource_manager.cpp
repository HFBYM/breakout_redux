#include"resource_manager.h"
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<stb.image.h>
//#include<vector>
#include<map>
#include"Shader.h"
#include"Texture.h"
// lib for math
//#include<glm.hpp>
//#include<gtc\type_ptr.hpp>
//#include<gtc/matrix_transform.hpp>


//initialize the static virants
static std::map<std::string, Texture2D> textures;
static std::map<std::string, Shader> shaders;

Shader& ResourceManager::getShader(const char* name)
{
	if (shaders.find(name) != shaders.end())
		return shaders[name];
	else
	{
		std::cout << "ERROR::GET_SHADER: failed to find the shader named " << name << std::endl;
		__debugbreak();
		return shaders[name];
	}
}
void ResourceManager::loadShader(const char* file, const char* name)
{
	std::ifstream ifs(file);
	if (!ifs.is_open())
	{
		std::cout << "ERROR::SHADER: failed to open " << file << std::endl;
		__debugbreak();
	}

	std::string line;
	std::stringstream ss[2];

	// use enum type for classification
	enum Type {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	Type type = NONE;

	// record if anything is found
	bool v_found = false, f_found = false;
	while (std::getline(ifs, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = VERTEX;
				v_found = true;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = FRAGMENT;
				f_found = true;
			}
			// if the type is find just skip the turn cause it the "#shader" couldn't be compiled
			continue;
		}
		//remember the endl which shader needs but ignored by getline
		ss[type] << line << std::endl;
	}
	if (!v_found || !f_found)
	{
		std::cout << "ERROR::SHADER: syntex error: " << (v_found ? NULL : "no vertex shader ")
			<< (f_found ? NULL : "no fragment shader ") << "named: " << name << " in\t" << file << std::endl;
		__debugbreak();
	}
	Shader shader(name);
	shader.compile(ss[VERTEX].str().c_str(), ss[FRAGMENT].str().c_str());

	// the data is moved by move copy and assignment function
	shaders[name] = std::move(shader);
}
Texture2D ResourceManager::loadTextureFromFile(const char* file, bool has_alpha)
{
	Texture2D texture;
	if (has_alpha)
	{
		texture.internal_format = GL_RGBA;
		texture.image_format = GL_RGBA;
	}

	// usually we need to turn up and down the texture cause OpenGL renders from the leftdown while
	// picture loaded from leftup. But it isn't here because the proj matrix has already turned
	// stbi_set_flip_vertically_on_load(1);

	int width, height;
	// the forth parm returns the channels of the image which is of no use
	unsigned char* image = stbi_load(file, &width, &height, 0,
		texture.image_format == GL_RGB ? 3 : 4);

	texture.generate(width, height, image);

	// the data in CPU is useless after sended to GPU
	stbi_image_free(image);

	return texture;
}
void ResourceManager::loadTexture(const char* file, bool has_alpha, const char* name)
{
	// the data is moved by move copy and assignment function
	textures[name] = loadTextureFromFile(file, has_alpha);
}
Texture2D& ResourceManager::getTexture(const char* name)
{
	if (textures.find(name) != textures.end())	//可被找到
		return textures[name];
	else
	{
		std::cout << "ERROR::GET_TEXTURE: failed to find the texture named " << name << std::endl;
		__debugbreak();
		return textures[name];
	}
}
void ResourceManager::init()
{
	//??json文件管理
	//load in shaders
	ResourceManager::loadShader(PROJECT_DIR"assets/shaders/postProcess.shader", "postProcess");
	ResourceManager::loadShader(PROJECT_DIR"assets/shaders/sprite.shader", "sprite");

	////正射投影即可 左上角是(0,0)与屏幕坐标对应	旋转中心在左上角 上下翻转同时纹理也上下反转???
	//glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(this->init_screen_width),
	//	static_cast<GLfloat>(this->init_screen_height), 0.0f, -1.0f, 1.0f);
	//ResourceManager::getShader("sprite").use().setInteger("image", 0);	//设定采样槽
	//ResourceManager::getShader("sprite").use().setMatrix4("proj", proj);	//设置正射投影

	ResourceManager::loadShader(PROJECT_DIR"assets/shaders/particle.shader", "particle");
	//ResourceManager::getShader("particle").use().setInteger("sprite", 0);	//设定采样槽
	//ResourceManager::getShader("particle").use().setMatrix4("proj", proj);	//设置正射投影

	//load in textures
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/background.jpg", GL_FALSE, "background");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/block.png", GL_FALSE, "block");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/basketball.png", GL_TRUE, "basketball");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/paddle.png", GL_TRUE, "paddle");

	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/particle.png", GL_TRUE, "particle");

	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/powerup_chaos.png", GL_FALSE, "tex_chaos");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/powerup_confuse.png", GL_FALSE, "tex_confuse");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/powerup_increase.png", GL_FALSE, "tex_size");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/powerup_passthrough.png", GL_FALSE, "tex_pass");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/powerup_speed.png", GL_FALSE, "tex_speed");
	ResourceManager::loadTexture(PROJECT_DIR"assets/textures/powerup_sticky.png", GL_FALSE, "tex_sticky");

}
void ResourceManager::clear()
{
	for (auto& iter : shaders)
		iter.second.clear();
	for (auto& iter : textures)
		glDeleteTextures(1, &iter.second.id);
}
