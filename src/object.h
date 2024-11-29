#pragma once
#include<glm.hpp>
class Object
{
public:
	~Object() = default;
	/// @brief must overwrite the construction and distruction ??
	Object(glm::vec2 pos, glm::vec2 size_draw, const char* id_name, unsigned int id_num):
		pos(pos), size_draw(size_draw), id_name(id_name), id_num(id_num){ }

	/// @brief pos is the leftdown point of the object
	glm::vec2 pos = glm::vec2(0.0f);

	/// @brief the size to draw the object
	glm::vec2 size_draw = glm::vec2(0.0f);

	/// @brief if it's false, this object will just be stored and seem like there isn't one
	bool to_work = true;

	const char* id_name = nullptr;
	unsigned int id_num = 0;
};
