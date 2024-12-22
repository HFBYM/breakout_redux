#pragma once
#include"renderObj.h"
#include"moveObj.h"
#include"mString.h"
#include"glm.hpp"
class Brick:public RenderObj, public MoveObj
{
public:
	enum BrickType {
		NONE = 0, SOLID, BLUE, GREEN, YELLOW, RED
	};

	Brick(const glm::vec2& pos, const glm::vec2& size, const mString& tex, BrickType type, 
		bool isSolid = false, glm::vec3 color = glm::vec3(1.0f)) :RenderObj(tex, "sprite", color), type(type), isSolid(isSolid), MoveObj(), Object(pos,size,"Brick"){ }

	/// @brief when a brick is distructed it should have cleaned all the logging
	~Brick() = default;

	virtual void log_all() override;
	virtual void detach_all() override;

	/// @brief when a brick is hit it should have cleaned all the logging
	virtual void do_collision(const mString& message, const glm::vec2& reflect, const glm::vec2& offset) override;
private:
	BrickType type = NONE;

	bool isSolid = false;
};