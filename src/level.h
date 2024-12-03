#pragma once
#include"brick.h"
#include<vector>
class mString;
class Level
{
public:
	Level(unsigned int id):id(id){}
	~Level();

	/// @brief initialize the level resource and it can't be reinitialized again
	/// @param path text file with level data
	/// @param levelWidth the level range
	/// @param levelHeight the level range
	void init(const mString& path, unsigned int levelWidth, unsigned int levelHeight);
	
	void log_renderer();

	void detach_renderer();

	/// @brief it can clear only once
	void clear();
	void Rotate();
	//??
	//bool isCompleted();	//���ؿ��Ƿ���� �����пɱ��ƻ��Ķ��ƻ���
private:
	//???��̬���عؿ�
	std::vector<Brick> bricks;

	// lives for each level
	unsigned int lives = 0;

	bool isInit = false;
	bool isClear = false;
	unsigned int id = 0;
};
