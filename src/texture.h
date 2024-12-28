#pragma once
#include"mString.h"
class Texture2D
{
private:
	unsigned int id = 0;
	unsigned int width = 0, height = 0;

	/// @brief the format of the texture
	unsigned int internal_format = 0;			

	/// @brief the format of the pircture
	unsigned int image_format = 0;			

	/// @brief how to wrap in s and t axis
	unsigned int wrap_s, wrap_t = 0;			

	/// @brief how to stretch when scaling
	unsigned int filter_min = 0, filter_max = 0;

	mString name;
	
	/// @brief it doesn't decide which slot to bind
	void generate(unsigned int width, unsigned int height, unsigned char* data);
public:
	Texture2D(const mString& name, unsigned int inFormat, unsigned int imaFormat, unsigned int width, unsigned int height, unsigned char* data);

	Texture2D(const Texture2D&) = delete;

	Texture2D& operator=(Texture2D&) = delete;

	~Texture2D();

	void bind() const;

	inline unsigned int getImage_Format() { return image_format; }
};