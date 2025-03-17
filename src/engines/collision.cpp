/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 19:10:23
 * @FilePath: \breakout_redux\src\engines\collision.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "engines/collision.h"

#include <algorithm>
#include <limits>
namespace collision
{
	struct CollisionResult
	{
		glm::vec2 direction;
		glm::vec2 correction;
	};
	namespace
	{
		// caltulate the time of collision and return the entry and exit time
		std::pair<float, float> computeCollisionTimes(float a_min, float a_max,
													  float b_min, float b_max, float velocity)
		{
			static constexpr float epsilon = 0.001f;
			if (velocity == 0.0f)
			{
				bool overlap = (b_min - a_max < epsilon) && (b_max - a_min > epsilon);
				return overlap ? std::pair(0.0f, std::numeric_limits<float>::infinity())
							   : std::pair(std::numeric_limits<float>::infinity(),
										   -std::numeric_limits<float>::infinity());
			}

			float entry = (a_min - b_max) / velocity;
			float exit = (a_max - b_min) / velocity;

			if (entry > exit)
			{
				auto temp = entry;
				entry = exit;
				exit = temp;
			}
			return {entry, exit};
		};

		CollisionResult check_collision(const CollisionData &one,
										const CollisionData &two, float deltatime)
		{
			CollisionResult result;
			result.direction = glm::vec2(0.0f);
			result.correction = glm::vec2(0.0f);

			glm::vec2 pos_one_pre = one.pos - one.velocity * deltatime;
			glm::vec2 pos_two_pre = two.pos - two.velocity * deltatime;

			glm::vec2 rel_velocity = two.velocity - one.velocity;

			// calculate the time of collision in x axis
			auto [x_entry, x_exit] = computeCollisionTimes(
				pos_one_pre.x, pos_one_pre.x + one.size.x,
				pos_two_pre.x, pos_two_pre.x + two.size.x,
				rel_velocity.x);

			// calculate the time of collision in y axis
			auto [y_entry, y_exit] = computeCollisionTimes(
				pos_one_pre.y, pos_one_pre.y + one.size.y,
				pos_two_pre.y, pos_two_pre.y + two.size.y,
				rel_velocity.y);

			float entry_time = std::max(x_entry, y_entry);
			float exit_time = std::min(x_exit, y_exit);

			// if no collision
			if (entry_time > exit_time || entry_time < 0.0f || entry_time > deltatime)
				return result;

			glm::vec2 pos_one_at_entry = pos_one_pre + one.velocity * entry_time;
			glm::vec2 pos_two_at_entry = pos_two_pre + two.velocity * entry_time;

			// ensure the direction
			if (x_entry > y_entry)
			{
				if (pos_two_pre.x + two.size.x < pos_one_pre.x)
					result.direction.x = 1.0f;
				else
					result.direction.x = -1.0f;
			}
			else
			{
				if (pos_two_pre.y + two.size.y < pos_one_pre.y)
					result.direction.y = 1.0f;
				else
					result.direction.y = -1.0f;
			}

			glm::vec2 new_velocity = one.velocity;
			if (result.direction.x)
				new_velocity.x = -new_velocity.x;
			else
				new_velocity.y = -new_velocity.y;

			float remaining_time = deltatime - entry_time;

			// pos after collision
			glm::vec2 corrected_position = pos_one_at_entry + new_velocity * remaining_time;

			result.correction = corrected_position - one.pos;

			return result;
		}
	} // namespace

	void Collision::collision(float dt)
	{
		std::map<unsigned int, bool> buffs_with_pad;
		const auto &data = getData();
		if (data.find("Pad") != data.end())
			for (auto &[_, pad] : data.at("Pad"))
			{
				if (data.find("Pad_Range") != data.end())
					for (auto &[__, pad_range] : data.at("Pad_Range"))
					{
						auto temp = check_collision(*pad, *pad_range, dt);
						if (temp.direction != glm::vec2(0, 0))
							pad->func("Pad_Range", temp.direction, temp.correction);
					}
				if (data.find("Range") != data.end())
					for (auto &[__, range] : data.at("Range"))
					{
						auto temp = check_collision(*pad, *range, dt);
						if (temp.direction != glm::vec2(0, 0))
							pad->func("Range", temp.direction, temp.correction);
					}
				if (data.find("Buff") != data.end())
					for (auto &[id, buff] : data.at("Buff"))
					{
						auto temp = check_collision(*pad, *buff, dt);
						if (temp.direction != glm::vec2(0, 0))
						{
							buffs_with_pad[id] = true;

							// using the function to pass the id
							pad->func("Buff", glm::vec2(static_cast<float>(id), 0.0f), glm::vec2(0.0f));
						}
					}
			}
		if (data.find("Buff") != data.end())
			for (auto &[buff, _] : buffs_with_pad)
				data.at("Buff").at(buff)->func("buff_with_pad", glm::vec2(0.0), glm::vec2(0.0));

		std::map<unsigned int, bool> buffs_with_range;
		if (data.find("Buff") != data.end())
			for (auto &[id, buff] : data.at("Buff"))
			{
				if (data.find("Buff_Range") != data.end())
					for (auto &[__, buff_range] : data.at("Buff_Range"))
					{
						auto temp = check_collision(*buff, *buff_range, dt);
						if (temp.direction != glm::vec2(0, 0))
							buffs_with_range[id] = true;
					}
			}
		if (data.find("Buff") != data.end())
			for (auto &[buff, _] : buffs_with_range)
				data.at("Buff").at(buff)->func("buff_with_range", glm::vec2(0.0), glm::vec2(0.0));

		// bricks would change the log data so it should be out of the loop
		std::map<unsigned int, bool> bricks;
		if (data.find("Ball") != data.end())
			for (auto &[_, ball] : data.at("Ball"))
			{
				if (data.find("Range") != data.end())
					for (auto &[__, ball_range] : data.at("Range"))
					{
						auto temp = check_collision(*ball, *ball_range, dt);
						if (temp.direction != glm::vec2(0, 0))
							ball->func("Ball_Range", temp.direction, temp.correction);
					}
				if (data.find("Pad") != data.end())
					for (auto &[__, pad] : data.at("Pad"))
					{
						auto temp = check_collision(*ball, *pad, dt);
						if (temp.direction != glm::vec2(0, 0))
							ball->func("Pad", temp.direction, temp.correction);
					}
				if (data.find("Brick") != data.end())
					for (auto &[id, brick] : data.at("Brick"))
					{
						auto temp = check_collision(*ball, *brick, dt);
						if (temp.direction != glm::vec2(0, 0))
						{
							ball->func("Brick", temp.direction, temp.correction);
							bricks[id] = true;
						}
					}
				if (data.find("Brick_Solid") != data.end())
					for (auto &[id, brick] : data.at("Brick_Solid"))
					{
						auto temp = check_collision(*ball, *brick, dt);
						if (temp.direction != glm::vec2(0, 0))
						{
							ball->func("Brick_Solid", temp.direction, temp.correction);
							brick->func("Ball", temp.direction, temp.correction);
						}
					}
			}
		if (data.find("Brick") != data.end())
			for (auto &[brick, _] : bricks)
				data.at("Brick").at(brick)->func("Ball", glm::vec2(0.0), glm::vec2(0.0));
	}
} // namespace collision
