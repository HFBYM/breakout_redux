/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-22 22:14:36
 * @FilePath: \breakout_redux\src\utils\texture.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "utils/texture.h"

#include <glad.h>
namespace texture
{
	struct Texture2D::TextureData
	{
		unsigned int id = 0;
		std::string name;
		explicit TextureData(const std::string &name)
			: name(name) {}
	};
	Texture2D::Texture2D(const std::string &name, unsigned int inFormat,
						 unsigned int imaFormat, unsigned int width, unsigned int height, unsigned char *data)
		: data(std::make_unique<TextureData>(name))
	{
		glGenTextures(1, &this->data->id);
		glBindTexture(GL_TEXTURE_2D, this->data->id);
		glTexImage2D(GL_TEXTURE_2D, 0, inFormat, width, height, 0,
					 imaFormat, GL_UNSIGNED_BYTE, data);

		// set the parm for texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &this->data->id);
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, this->data->id);
	}
} // namespace texture
