#include "moveObj.h"
#include "movement.h"
#include "check.h"
#include "collision.h"
MoveObj::~MoveObj()
{
	ASSERT_LOG(!is_log_move, "ERROR::MOVEOGJ: " << id_name.getStr() << " " << id_num << "isn't detached in movement");
	ASSERT_LOG(!is_log_collision, "ERROR::COLLISIONOBJ: " << id_name.getStr() << " " << id_num << "isn't detached in collision");
}

void MoveObj::log_move()
{
	if (!is_log_move)
		Movement::logger.log(id_name, id_num, new Movement::LogData(pos, velocity, accelerate));
	is_log_move = true;
}

void MoveObj::detach_move()
{
	if (is_log_move)
		Movement::logger.detach(id_name, id_num);
	is_log_move = false;
}
void MoveObj::log_collision()
{
	if (!is_log_collision)
	{
		std::function<void(const mString&, const glm::vec2&, const glm::vec2 &)> func = [this](const mString& message,const glm::vec2& reflect, const glm::vec2 &offset)
		{ this->do_collision(message, reflect, offset); };
		Collision::logger.log(id_name, id_num, new Collision::CollisionData(pos, size, func, velocity));
	}
	is_log_collision = true;
}

void MoveObj::detach_collision()
{
	if (is_log_collision)
		Collision::logger.detach(id_name, id_num);
	is_log_collision = false;
}
