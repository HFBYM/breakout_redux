#include"texture.h"
#include<iostream>
#include<glad.h>

Texture2D::Texture2D(const char* name, unsigned int inFormat, unsigned int imaFormat)
	:internal_format(inFormat),image_format(imaFormat), wrap_t(GL_REPEAT), wrap_s(GL_REPEAT), 
	filter_max(GL_LINEAR), filter_min(GL_LINEAR), name(name)
{
	glGenTextures(1, &this->id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data) 
{
	this->width = width;
	this->height = height;
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0,
		this->image_format, GL_UNSIGNED_BYTE, data);
	
	// set the parm for texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
	glBindTexture(GL_TEXTURE_2D, 0);
	isGenerate = true;
}
void Texture2D::bind() const
{
	if (!isGenerate)
	{
		std::cout << "ERROR::TEXTURE: bind texture " << name << " which isn't generated" << std::endl;
		__debugbreak();
	}
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture2D::clear()
{
	if (!isGenerate)
	{
		std::cout << "ERROR::TEXTURE: clear texture " << name << " which isn't generated" << std::endl;
		__debugbreak();
	}
	glDeleteTextures(1, &this->id);
	isGenerate = false;
}
