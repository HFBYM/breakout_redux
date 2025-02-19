#include "collision.h"
#include <vector>

// TODO 完善碰撞检测 斜角碰撞反弹 文件分类
/// @brief check collision and return the direction of the force on the first object assuming the second object is static
/// @return first is the direction of the force, second is the offset
static std::pair<glm::vec2, glm::vec2> check_collision(const glm::vec2 &pos_one, const glm::vec2 &size_one, const glm::vec2 &velocity_one, const glm::vec2 &pos_two, const glm::vec2 &size_two, const glm::vec2 &velocity_two, float dt)
{
	// collision happened
	if (pos_one.x + size_one.x > pos_two.x && pos_two.x + size_two.x > pos_one.x && pos_one.y + size_one.y > pos_two.y && pos_two.y + size_two.y > pos_one.y)
	{
		glm::vec2 pos_1_to_2 = pos_one - pos_two;
		glm::vec2 velocity_1_to_2 = velocity_one - velocity_two;
		glm::vec2 pre_pos = pos_1_to_2 - velocity_1_to_2 * dt;

		float xoffset = velocity_1_to_2.x * dt;
		float yoffset = velocity_1_to_2.y * dt;
		glm::vec2 direct = glm::vec2(0, 0);

// insufficient precision
#ifndef EPSILON
#define EPSILON 0.001f
#endif
		if (size_two.x < pre_pos.x + EPSILON)
		{
			xoffset = size_two.x - pre_pos.x;
			direct.x = 1;
		}
		else if (pre_pos.x + size_one.x < EPSILON)
		{
			xoffset = -size_one.x - pre_pos.x;
			direct.x = -1;
		}
		if (size_two.y < pre_pos.y + EPSILON)
		{
			yoffset = size_two.y - pre_pos.y;
			direct.y = 1;
		}
		else if (pre_pos.y + size_one.y < EPSILON)
		{
			yoffset = -size_one.y - pre_pos.y;
			direct.y = -1;
		}
		if (direct.x && direct.y)
		{
			if (abs(xoffset / velocity_1_to_2.x) < abs(yoffset / velocity_1_to_2.y))
			{
				direct.y = 0;
				yoffset = velocity_1_to_2.y * dt;
			}
			else
			{
				direct.x = 0;
				xoffset = velocity_1_to_2.x * dt;
			}
		}
		return {direct, glm::vec2(-velocity_1_to_2.x * dt + xoffset, -velocity_1_to_2.y * dt + yoffset)};
#undef EPSILON
	}
	return {glm::vec2(0, 0), glm::vec2(0, 0)};
}

/// @brief access collision data and process
void Collision::collision(float dt)
{
	std::map<unsigned int, bool> buffs_with_pad;
	for (auto &[_, pad] : data["Pad"])
	{
		for (auto &[__, pad_range] : data["Pad_Range"])
		{
			auto temp = check_collision(pad->pos, pad->size, pad->velocity, pad_range->pos, pad_range->size, pad_range->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				pad->func("Pad_Range", temp.first, temp.second);
		}
		for (auto &[__, range] : data["Range"])
		{
			auto temp = check_collision(pad->pos, pad->size, pad->velocity, range->pos, range->size, range->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				pad->func("Range", temp.first, temp.second);
		}
		for (auto &[id, buff] : data["Buff"])
		{
			auto temp = check_collision(pad->pos, pad->size, pad->velocity, buff->pos, buff->size, buff->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
			{
				buffs_with_pad[id] = true;

				// using the function to pass the id
				pad->func("Buff", glm::vec2(static_cast<float>(id), 0.0f), glm::vec2(0.0f));
			}
		}
	}

	for (auto &[buff, _] : buffs_with_pad)
		data["Buff"][buff]->func("buff_with_pad", glm::vec2(0.0), glm::vec2(0.0));

	std::map<unsigned int, bool> buffs_with_range;
	for (auto &[id, buff] : data["Buff"])
	{
		for (auto &[__, buff_range] : data["Buff_Range"])
		{
			auto temp = check_collision(buff->pos, buff->size, buff->velocity, buff_range->pos, buff_range->size, buff_range->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				buffs_with_range[id] = true;
		}
	}

	for (auto &[buff, _] : buffs_with_range)
		data["Buff"][buff]->func("buff_with_range", glm::vec2(0.0), glm::vec2(0.0));

	// bricks would change the log data so it should be out of the loop
	std::map<unsigned int, bool> bricks;
	for (auto &[_, ball] : data["Ball"])
	{
		for (auto &[__, ball_range] : data["Range"])
		{
			auto temp = check_collision(ball->pos, ball->size, ball->velocity, ball_range->pos, ball_range->size, ball_range->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				ball->func("Ball_Range", temp.first, temp.second);
		}
		for (auto &[__, pad] : data["Pad"])
		{
			auto temp = check_collision(ball->pos, ball->size, ball->velocity, pad->pos, pad->size, pad->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				ball->func("Pad", temp.first, temp.second);
		}
		for (auto &[id, brick] : data["Brick"])
		{
			auto temp = check_collision(ball->pos, ball->size, ball->velocity, brick->pos, brick->size, brick->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
			{
				ball->func("Brick", temp.first, temp.second);
				bricks[id] = true;
			}
		}
		for (auto &[id, brick] : data["Brick_Solid"])
		{
			auto temp = check_collision(ball->pos, ball->size, ball->velocity, brick->pos, brick->size, brick->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
			{
				ball->func("Brick_Solid", temp.first, temp.second);
				brick->func("Ball", temp.first, temp.second);
			}
		}
	}

	for (auto &[brick, _] : bricks)
		data["Brick"][brick]->func("Ball", glm::vec2(0.0), glm::vec2(0.0));
}