#include"resource_manager.h"
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>
#include<stb.image.h>
#include<map>
#include<glad.h>
#include"shader.h"
#include"texture.h"
// lib for math
//#include<glm.hpp>
//#include<gtc\type_ptr.hpp>
//#include<gtc/matrix_transform.hpp>
#define CHECK_STATUS() if(!isInit){\
	std::cout<<"ERROR::RESOURCE: "<<__FUNCTION__<<" operate resource manager not initialized"<<std::endl;\
	__debugbreak();}\
	if(isClear){\
	std::cout<<"ERROR::RESOURCE: "<<__FUNCTION__<<" operate resource manager cleared"<<std::endl;\
	__debugbreak();}

//initialize the static virants
static std::map<const char*, Texture2D*> textures;
static std::map<const char*, Shader*> shaders;
static bool isInit = false;
static bool isClear = false;

static void loadShader(const char* file, const char* name)
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
	shaders[name] = new Shader(name);
	shaders[name]->compile(ss[VERTEX].str().c_str(), ss[FRAGMENT].str().c_str());
}

/// @brief load texture2D from file
/// @param file filepath
/// @param has_alpha decides whether or not this texture has alpha channel
/// @param name the texture name
static void loadTexture(const char* file, bool has_alpha, const char* name)
{
	textures[name] = new Texture2D(name, has_alpha ? GL_RGBA : GL_RGB, has_alpha ? GL_RGBA : GL_RGB);

	// usually we need to turn up and down the texture cause OpenGL renders from the leftdown while
	// picture loaded from leftup. But it isn't here because the proj matrix has already turned
	// stbi_set_flip_vertically_on_load(1);

	int width, height;

	// the forth parm returns the channels of the image which is of no use
	unsigned char* image = stbi_load(file, &width, &height, 0,
		textures[name]->getImage_Format() == GL_RGB ? 3 : 4);

	textures[name]->generate(width, height, image);

	// the data in CPU is useless after sended to GPU
	stbi_image_free(image);
}

Shader& ResourceManager::getShader(const char* name)
{
	CHECK_STATUS();
	if (shaders.find(name) != shaders.end())
		return *shaders[name];
	else
	{
		std::cout << "ERROR::GET_SHADER: failed to find the shader " << name << std::endl;
		__debugbreak();
		return *shaders[name];
	}
}
Texture2D& ResourceManager::getTexture(const char* name)
{
	CHECK_STATUS();
	if (textures.find(name) != textures.end())
		return *textures[name];
	else
	{
		std::cout << "ERROR::GET_TEXTURE: failed to find the texture " << name << std::endl;
		__debugbreak();
		return *textures[name];
	}
}
void ResourceManager::init()
{
	isInit = true;
	//??json文件管理
	//load in shaders
	loadShader(PROJECT_DIR"/assets/shaders/postProcess.shader", "postProcess");
	loadShader(PROJECT_DIR"/assets/shaders/sprite.shader", "sprite");

	////正射投影即可 左上角是(0,0)与屏幕坐标对应	旋转中心在左上角 上下翻转同时纹理也上下反转???
	//glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(this->init_screen_width),
	//	static_cast<GLfloat>(this->init_screen_height), 0.0f, -1.0f, 1.0f);
	//ResourceManager::getShader("sprite").use().setInteger("image", 0);	//设定采样槽
	//ResourceManager::getShader("sprite").use().setMatrix4("proj", proj);	//设置正射投影

	loadShader(PROJECT_DIR"/assets/shaders/particle.shader", "particle");
	//ResourceManager::getShader("particle").use().setInteger("sprite", 0);	//设定采样槽
	//ResourceManager::getShader("particle").use().setMatrix4("proj", proj);	//设置正射投影

	//load in textures
	loadTexture(PROJECT_DIR"/assets/textures/background.jpg", false, "background");
	loadTexture(PROJECT_DIR"/assets/textures/block.png", false, "block");
	loadTexture(PROJECT_DIR"/assets/textures/block_solid.png", false, "block_solid");
	loadTexture(PROJECT_DIR"/assets/textures/basketball.png", true, "basketball");
	loadTexture(PROJECT_DIR"/assets/textures/paddle.png", true, "paddle");

	loadTexture(PROJECT_DIR"/assets/textures/particle.png", true, "particle");

	loadTexture(PROJECT_DIR"/assets/textures/powerup_chaos.png", false, "tex_chaos");
	loadTexture(PROJECT_DIR"/assets/textures/powerup_confuse.png", false, "tex_confuse");
	loadTexture(PROJECT_DIR"/assets/textures/powerup_increase.png", false, "tex_size");
	loadTexture(PROJECT_DIR"/assets/textures/powerup_passthrough.png", false, "tex_pass");
	loadTexture(PROJECT_DIR"/assets/textures/powerup_speed.png", false, "tex_speed");
	loadTexture(PROJECT_DIR"/assets/textures/powerup_sticky.png", false, "tex_sticky");

}
void ResourceManager::clear()
{
	CHECK_STATUS();
	isClear = true;
	for (auto& iter : shaders)
	{
		iter.second->clear();
		delete iter.second;
	}
	for (auto& iter : textures)
	{
		iter.second->clear();
		delete iter.second;
	}
	shaders.clear();
	textures.clear();
}
