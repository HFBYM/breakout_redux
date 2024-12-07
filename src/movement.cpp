#include"movement.h"
#include"check.h"

static bool isClear = false;

static std::map<mString, std::map<unsigned int, Movement::LogData*>>* log_datas = new std::map<mString, std::map<unsigned int, Movement::LogData*>>;
Logger<Movement::LogData> Movement::logger(*log_datas);

void Movement::move(float  dt)
{
	ASSERT_LOG(!isClear, "ERROR::MOVEMENT:: " << __FUNCTION__ << " uses Movement cleared");
	for(auto& i:*log_datas)
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
	logger.clear();
	if(log_datas)
	{
		delete log_datas;
		log_datas = nullptr;
	}
}
