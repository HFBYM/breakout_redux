#include"movement.h"
#include<map>
#include"check.h"

static bool isClear = false;
///TODOÕûºÏ
struct LogData
{
	glm::vec2& pos;
	glm::vec2& volecity;
	glm::vec2& accelerate;
	LogData(glm::vec2& pos, glm::vec2& volecity, glm::vec2& accelerate):pos(pos), volecity(volecity), accelerate(accelerate){}
};
static std::map<mString, std::map<unsigned int, LogData*>> log_datas;

void Movement::log(const mString& id_type, unsigned int id_num, glm::vec2& pos, glm::vec2& volecity, glm::vec2& accelerate)
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	log_datas[id_type][id_num] = new LogData( pos, volecity, accelerate );
}

void Movement::detach(const mString& id_type, unsigned int  id_num)
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	if (log_datas[id_type][id_num])
		delete log_datas[id_type][id_num];
	log_datas[id_type].erase(id_num);
}

void Movement::move(float  dt)
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	for(auto& i:log_datas)
		for (auto& j : i.second)
		{
			LogData& temp = *j.second;
			temp.volecity += temp.accelerate * dt;
			temp.pos += temp.volecity * dt;
		}
}

struct CollisionData
{
	glm::vec2& pos;
	glm::vec2& size;
	Movement::FuncType func;
	CollisionData(glm::vec2& pos, glm::vec2& size, Movement::FuncType func):
		pos(pos), size(size), func(func){}
};

static std::map<mString, std::map<unsigned int, CollisionData*>> collision_data;

void Movement::log_collision(const mString& type, Movement::FuncType func, unsigned int id, glm::vec2& pos, glm::vec2& size)
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	if(func)
		collision_data[type][id] = new CollisionData(pos, size, func);
}

void Movement::detach_collision(const mString& type, unsigned int id_num)
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	if (collision_data[type][id_num])
		delete collision_data[type][id_num];
	collision_data[type].erase(id_num);
}

/// @brief check if two object is collision
static bool check_collision(glm::vec2& pos_one, glm::vec2& size_one, glm::vec2& pos_two, glm::vec2& size_two)
{
   bool collisionX = pos_one.x + size_one.x >= pos_two.x && pos_two.x + size_two.x >= pos_one.x;
   bool collisionY = pos_one.y + size_one.y >= pos_two.y && pos_two.y + size_two.y >= pos_one.y;
   return collisionX && collisionY;
}

void Movement::collision() 
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	for (auto& [_, player] : collision_data["Player"])
	{
		unsigned int count = 0;
		for(auto&[__, player_range] : collision_data["Player_Range"])
		{
			if (check_collision(player->pos, player->size, player_range->pos, player_range->size))
			{
				switch (count)
				{
				case 0: player->func("left");	break;
				case 1:	player->func("right");	break;
				case 2:	player->func("up");		break;
				case 3:	player->func("down");	break;
				default:player->func("default");break;
				}
			}
			count++;
		}
	}
}


void Movement::clear()
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	isClear = true;
	for (auto& i : log_datas)
	{
		for (auto& j : i.second)
			if(j.second)
				delete j.second;
		i.second.clear();
	}
	log_datas.clear();
	for (auto& i : collision_data)
	{
		for (auto& j : i.second)
			if (j.second)
				delete j.second;
		i.second.clear();
	}
	collision_data.clear();
}
