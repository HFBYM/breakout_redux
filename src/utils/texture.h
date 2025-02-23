/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-22 22:05:44
 * @FilePath: \breakout_redux\src\utils\texture.h
 * Copyright (c) 2025 by Clare, All Rights Reserved. 
 */
#pragma once
#include<string>
#include<memory>
namespace texture{
class Texture2D
{
public:
	Texture2D(const std::string& name, unsigned int inFormat,
		unsigned int imaFormat, unsigned int width, unsigned int height, unsigned char* data);

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(Texture2D&) = delete;

	~Texture2D();
	void bind() const;
private:
	struct TextureData;
	std::unique_ptr<TextureData> data;
};
} // namespace texture
