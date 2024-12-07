#include"collision.h"
#include<map>
#include"check.h"

static bool isClear = false;
struct CollisionData
{
	glm::vec2& pos;
	glm::vec2& size;
	Collision::FuncType func;
	CollisionData(glm::vec2& pos, glm::vec2& size, Collision::FuncType func):
		pos(pos), size(size), func(func){}
};

static std::map<mString, std::map<unsigned int, CollisionData*>> collision_data;

void Collision::log(const mString &type, FuncType func, unsigned int id, glm::vec2 &pos, glm::vec2 &size)
{
    	ASSERT_LOG(!isClear, "ERROR::Collision:: " << __FUNCTION__ << " uses Collision cleared");
	if(func)
		collision_data[type][id] = new CollisionData(pos, size, func);
}

void Collision::detach(const mString &type, unsigned int id_num)
{	
    ASSERT_LOG(!isClear, "ERROR::Collision:: " << __FUNCTION__ << " uses Collision cleared");
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

void Collision::collision()
{
    	ASSERT_LOG(!isClear, "ERROR::Collision:: " << __FUNCTION__ << " uses Collision cleared");
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

void Collision::clear()
{
    ASSERT_LOG(!isClear, "ERROR::Collision:: " << __FUNCTION__ << " uses Collision cleared");
	for (auto& i : collision_data)
	{
		for (auto& j : i.second)
			if (j.second)
				delete j.second;
		i.second.clear();
	}
	collision_data.clear();
}
