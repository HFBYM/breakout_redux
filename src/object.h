#pragma once
#include"glm.hpp"
#include"mString.h"
class Object
{
public:
	~Object() = default;

	Object(const glm::vec2& pos, const glm::vec2& size_draw, const mString& id_name, unsigned int id_num):
		pos(pos), size_draw(size_draw), id_name(id_name), id_num(id_num){ }

	/// @brief pos is the leftdown point of the object
	glm::vec2 pos = glm::vec2(0.0f);

	/// @brief the size to draw the object
	glm::vec2 size_draw = glm::vec2(0.0f);

	/// @brief if it's false, this object will just be stored and seem like there isn't one??
	bool to_work = true;

	mString id_name;
	unsigned int id_num = 0;

	virtual void log_all() = 0;
	virtual void detach_all() = 0;
};
