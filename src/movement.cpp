#include"movement.h"
#include<map>
#include"check.h"

static bool isClear = false;
///TODO 整合
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
}
