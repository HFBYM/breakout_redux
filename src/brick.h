#pragma once
#include "renderObj.h"
#include "moveObj.h"
#include "glm.hpp"
#include <string>
class Brick : public RenderObj, public MoveObj
{
public:
	enum class BrickType
	{
		NONE = 0,
		SOLID,
		BLUE,
		GREEN,
		YELLOW,
		RED
	};

	Brick(const glm::vec2 &pos, const glm::vec2 &size, const std::string &tex, BrickType type, bool isSolid = false, glm::vec3 color = glm::vec3(1.0f)) : RenderObj(tex, "sprite", glm::vec4(color, 1.0f)), type(type), isSolid(isSolid), MoveObj(), Object(pos, size, getName(isSolid)) {}

	/// @brief when a brick is distructed it should have cleaned all the logging
	~Brick() = default;

	bool isDestroyed() const { return !is_log_renderer&&!isSolid; }

	virtual void log_all() override;
	virtual void detach_all() override;

	/// @brief when a brick is hit it should have cleaned all the logging and generate particles
	virtual void do_collision(const std::string &message, const glm::vec2 &reflect, const glm::vec2 &offset) override;

private:
	BrickType type;

	bool isSolid = false;
	std::string getName(bool isSolid) { return isSolid ? "Brick_Solid" : "Brick"; }
};