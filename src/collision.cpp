#include "collision.h"
#include<vector>

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
	// bricks would change the log data so it should be out of the loop
	std::vector<unsigned int> bricks;
	for (auto &[_, player] : data["Player"])
	{
		for (auto &[__, player_range] : data["Player_Range"])
		{
			auto temp = check_collision(player->pos, player->size, player->velocity, player_range->pos, player_range->size, player_range->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				player->func("Player_Range", temp.first, temp.second);
		}
	}

	for (auto &[_, ball] : data["Ball"])
	{
		for (auto &[__, ball_range] : data["Ball_Range"])
		{
			auto temp = check_collision(ball->pos, ball->size, ball->velocity, ball_range->pos, ball_range->size, ball_range->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				ball->func("Ball_Range", temp.first, temp.second);
		}
		for (auto &[__, player] : data["Player"])
		{
			auto temp = check_collision(ball->pos, ball->size, ball->velocity, player->pos, player->size, player->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
				ball->func("Player", temp.first, temp.second);
		}
		for (auto &[id, brick] : data["Brick"])
		{
			auto temp = check_collision(ball->pos, ball->size, ball->velocity, brick->pos, brick->size, brick->velocity, dt);
			if (temp.first != glm::vec2(0, 0))
			{
				ball->func("Brick", temp.first, temp.second);
				bricks.push_back(id);
			}
		}
	}
	for (auto &brick : bricks)
		data["Brick"][brick]->func("Ball", glm::vec2(0.0), glm::vec2(0.0));
}