#include"movement.h"
#include<map>
///TODO整合
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
	log_datas[id_type][id_num] = new LogData( pos, volecity, accelerate );
}

void Movement::detach(const mString& id_type, unsigned int  id_num)
{
	if (log_datas[id_type][id_num])
		delete log_datas[id_type][id_num];
	log_datas[id_type].erase(id_num);
}

void Movement::work(float  dt)
{
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
	CollisionObj& obj;
	void(CollisionObj::* func_p)(const mString&);
	CollisionData(glm::vec2& pos, glm::vec2& size, CollisionObj& obj, void(CollisionObj::* func_p)(const mString&)):
		pos(pos), size(size), obj(obj), func_p(func_p){}
};

static std::map<mString, std::map<unsigned int, CollisionData*>> collision_data;
///TODO整合走 空气墙
void Movement::log_collision(const mString& type, CollisionObj& obj, void(CollisionObj::* func_p)(const mString&), unsigned int id, glm::vec2& pos, glm::vec2& size)
{
	collision_data[type][id] = new CollisionData(pos, size, obj, func_p);
}

void Movement::detach_collision(const mString& type, unsigned int id_num)
{
	if (collision_data[type][id_num])
		delete collision_data[type][id_num];
	collision_data[type].erase(id_num);
}
static void do_collision()
{
	for (auto& i : collision_data["Player"])
	{
		CollisionData& temp = *i.second;
	}
}
