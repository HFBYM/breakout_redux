#pragma once
#include"brick.h"
#include<vector>
#include<memory>
class Level
{
public:
	/// @param path text file with level data
	Level(unsigned int id, const mString& path, unsigned int levelWidth, unsigned int levelHeight);
	~Level() = default;
	
	void log_renderer();
	void detach_renderer();
	void log_collision();
	void detach_collision();
	void log_all();
	void detach_all();

	void Rotate();

	//bool isCompleted();	//���ؿ��Ƿ���� �����пɱ��ƻ��Ķ��ƻ���
private:
	//TODO��̬���عؿ�
	std::vector<std::unique_ptr<Brick>> bricks;

	// lives for each level
	unsigned int lives = 0;

	unsigned int id = 0;
};
