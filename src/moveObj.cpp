#include "moveObj.h"
#include "movement.h"
#include "collision.h"
MoveObj::~MoveObj()
{
	detach_collision();
	detach_move();
}

void MoveObj::log_move()
{
	if (!is_log_move)
		Movement::instance().log(id_name, id_num, std::make_unique<Movement::Data>(pos, velocity, accelerate));
	is_log_move = true;
}

void MoveObj::detach_move()
{
	if (is_log_move)
		Movement::instance().detach(id_name, id_num);
	is_log_move = false;
}
void MoveObj::log_collision()
{
	if (!is_log_collision)
	{
		Collision::FuncType func = [this](const std::string &message, const glm::vec2 &reflect, const glm::vec2 &offset)
		{ this->do_collision(message, reflect, offset); };
		Collision::instance().log(id_name, id_num, std::make_unique<Collision::Data>(pos, size, func, velocity));
	}
	is_log_collision = true;
}

void MoveObj::detach_collision()
{
	if (is_log_collision)
		Collision::instance().detach(id_name, id_num);
	is_log_collision = false;
}
