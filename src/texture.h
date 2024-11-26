#pragma once
#include<glad.h>
class Texture2D
{
public:
	GLuint id;
	GLuint width, height;
	GLuint internal_format;			//����ĸ�ʽ
	GLuint image_format;			//ͼƬ�ĸ�ʽ
	GLuint wrap_s, wrap_t;			//���ݷ�����Ʒ�ʽ
	GLuint filter_min, filter_max;	//�Ŵ����Сʱ��ͼƬ������ʽ

	Texture2D();


	Texture2D(Texture2D&&) = default;

	//�����ƶ���ֵ��� ע���ʱ������ֵ����ѱ�ɾ��
	Texture2D& operator=(Texture2D&&) = default;

	void generate(GLuint width, GLuint height, unsigned char* data);
	void bind() const;
};