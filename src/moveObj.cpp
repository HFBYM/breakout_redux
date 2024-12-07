#include"moveObj.h"
#include"movement.h"
#include"check.h"
MoveObj::~MoveObj()
{
	ASSERT_LOG(!is_log_move, "ERROR::MOVEOGJ: " << id_name.getStr() << " "
		<< id_num << "isn't detached in movement");
}

void MoveObj::log_move()
{
	if (!is_log_move)
		Movement::logger.log(id_name, id_num, {pos, velocity, accelerate});
	is_log_move = true;
}

void MoveObj::detach_move()
{
	if (is_log_move)
		Movement::logger.detach(id_name, id_num);
	is_log_move = false;
}