#pragma once
#include"object.h"
class Brick:public Object
{
public:
	enum BrickType {
		NONE = 0, SOLID, BLUE, GREEN, YELLOW, RED
	};

	Brick(glm::vec2 pos, glm::vec2 size, const char* tex, BrickType type, glm::vec3 color = glm::vec3(1.0f));
	~Brick();

	void log_renderer();
	void detach_renderer();
private:
	BrickType type = NONE;

	const char* tex = nullptr;
	glm::vec3 color = glm::vec3(0.0f);
	float rotate = 0.0f;
};