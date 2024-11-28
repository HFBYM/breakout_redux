#pragma once
class Texture2D
{
private:
	unsigned int id = 0;
	unsigned int width = 0, height = 0;

	/// @brief the format of the texture
	unsigned int internal_format;			

	/// @brief the format of the pircture
	unsigned int image_format;			

	/// @brief how to wrap in s and t axis
	unsigned int wrap_s, wrap_t;			

	/// @brief how to stretch when scaling
	unsigned int filter_min, filter_max;

	const char* name;
	bool isGenerate = false;
public:
	Texture2D(const char* name, unsigned int inFormat, unsigned int imaFormat);
	Texture2D() = default;

	Texture2D& operator=(Texture2D&&) = default;

	/// @brief it doesn't decide which slot to bind
	void generate(unsigned int width, unsigned int height, unsigned char* data);

	void bind() const;

	/// @brief delete the texture
	void clear();

	inline unsigned int getImage_Format() { return image_format; }
};