#include "texture.h"
#include <glad.h>

Texture2D::Texture2D(const std::string &name, unsigned int inFormat, unsigned int imaFormat, unsigned int width, unsigned int height, unsigned char *data)
	: internal_format(inFormat), image_format(imaFormat), wrap_t(GL_REPEAT), wrap_s(GL_REPEAT),
	  filter_max(GL_LINEAR), filter_min(GL_LINEAR), name(name)
{
	glGenTextures(1, &this->id);
	this->generate(width, height, data);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &this->id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char *data)
{
	this->width = width;
	this->height = height;
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);

	// set the parm for texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}
