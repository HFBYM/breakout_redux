/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:07:17
 * @FilePath: \breakout_redux\src\obj_for_engines\moveObj.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "obj_for_engines/moveObj.h"

#include <memory>
#include <string>

#include "engines/movement.h"
#include "engines/collision.h"
#include "moveObj.h"
namespace move_obj
{
	struct MoveObj::MoveObjData
	{
		bool is_log_move = false;
		bool is_log_collision = false;
		glm::vec2 velocity;
		glm::vec3 accelerate;
		explicit MoveObjData(const glm::vec2 &velocity)
			: velocity(velocity), accelerate(glm::vec3(0.0f)) {}
	};

	MoveObj::MoveObj(const glm::vec2 &v) : data(std::make_unique<MoveObjData>(v)), Object("MoveObj")
	{
	}
	MoveObj::MoveObj(const std::string &id_name, const glm::vec2 &pos, const glm::vec2 &size)
		: Object(pos, size, id_name), data(std::make_unique<MoveObjData>(glm::vec2(0.0f)))
	{
	}
	MoveObj::~MoveObj()
	{
		detach_collision();
		detach_move();
	}

	void MoveObj::log_move()
	{
		using movement::Movement;
		if (!data->is_log_move)
			Movement::instance().log(getIdName(), getIdNum(),
									 std::make_unique<movement::MovementData>(&const_cast<glm::vec2&>(getPos()),
									 &data->velocity, &data->accelerate));
		data->is_log_move = true;
	}

	void MoveObj::detach_move()
	{
		using movement::Movement;
		if (data->is_log_move)
			Movement::instance().detach(getIdName(), getIdNum());
		data->is_log_move = false;
	}
	void MoveObj::log_collision()
	{
		using collision::Collision;
		if (!data->is_log_collision)
		{
			auto func = [this](const std::string &message, const glm::vec2 &reflect, const glm::vec2 &offset)
			{ this->do_collision(message, reflect, offset); };
			Collision::instance().log(getIdName(), getIdNum(),
									  std::make_unique<collision::CollisionData>(getPos(), getSize(), func, data->velocity));
		}
		data->is_log_collision = true;
	}

	void MoveObj::detach_collision()
	{
		using collision::Collision;
		if (data->is_log_collision)
			Collision::instance().detach(getIdName(), getIdNum());
		data->is_log_collision = false;
	}
	void MoveObj::setVelocity(const glm::vec2 &velocity)
	{
		data->velocity = velocity;
	}
	const glm::vec2 &MoveObj::getVelocity() const
	{
		return data->velocity;
	}
    void MoveObj::setAcceleration(const glm::vec3 &acceleration)
    {
		data->accelerate = acceleration;
    }
    const glm::vec3 &MoveObj::getAcceleration() const
    {
        return data->accelerate;
    }
} // namespace move_obj
