#pragma once
#include<glad.h>
class Texture2D
{
public:
	GLuint id;
	GLuint width, height;
	GLuint internal_format;			//纹理的格式
	GLuint image_format;			//图片的格式
	GLuint wrap_s, wrap_t;			//横纵方向缠绕方式
	GLuint filter_min, filter_max;	//放大或缩小时的图片伸缩方式

	Texture2D();


	Texture2D(Texture2D&&) = default;

	//重载移动赋值语句 注意此时拷贝赋值语句已被删除
	Texture2D& operator=(Texture2D&&) = default;

	void generate(GLuint width, GLuint height, unsigned char* data);
	void bind() const;
};