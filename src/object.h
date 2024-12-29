#pragma once
#include"glm.hpp"
#include"mString.h"

/// @brief the base class for all objects and it's not a abstract class
class Object
{
public:
	~Object() = default;

	/// @brief by default the id_num will add up from 0
	Object(const glm::vec2& pos, const glm::vec2& size, const mString& id_name, 
		unsigned int id_num = getId_num()):
		pos(pos), size(size), id_name(id_name), id_num(id_num){ }

	/// @brief this is a special constructor for some class or object which has no size or pos
	Object(const mString& type) : id_name(type),id_num(getId_num()) {}

	virtual void log_all() {}
	virtual void detach_all() {}
protected:
	/// @brief pos is the leftdown point of the object
	glm::vec2 pos = glm::vec2(0.0f);

	glm::vec2 size = glm::vec2(0.0f);
	mString id_name;
	unsigned int id_num = 0;
private:
	inline static unsigned int getId_num() { static unsigned int i = 0; return i++; }
};
