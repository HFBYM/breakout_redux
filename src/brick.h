#pragma once
#include"object.h"
#include"mString.h"
#include"glm.hpp"
class Brick:public Object
{
public:
	enum BrickType {
		NONE = 0, SOLID, BLUE, GREEN, YELLOW, RED
	};

	Brick(const glm::vec2& pos, const glm::vec2& size, const mString& tex, BrickType type, 
		bool isSolid = false, glm::vec3 color = glm::vec3(1.0f));

	/// @brief when a brick is distructed it should have cleaned all the logging
	~Brick();

	/// @brief user can log and detach any times
	void log_renderer();
	void detach_renderer();

	void log_all();
	void detach_all();
private:
	BrickType type = NONE;

	bool isSolid = false;

	///??变量与渲染器打包
	mString tex;
	glm::vec3 color = glm::vec3(0.0f);
	float rotate = 0.0f;
	/// @brief 多个其他变量??
	bool is_log_renderer = false;
};