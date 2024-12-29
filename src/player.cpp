#include "player.h"
#include <iostream>
#include "keyval.h"
#include <memory>

std::unique_ptr<std::unique_ptr<MoveObj>[]> Player::player_range_p(std::make_unique<std::unique_ptr<MoveObj>[]>(4));

Player::Player(unsigned int width, unsigned int height, glm::vec3 color, glm::vec2 size)
	: RenderObj("paddle", "sprite", color), init_screen_width(width), init_screen_height(height), Object(glm::vec2((width - size.x) / 2, height - size.y), size, "Player")
{
	static bool is_init_range = false;
	if (!is_init_range)
	{
		player_range_p[0] = std::make_unique<MoveObj>("Player_Range", glm::vec2(-10.0f, init_screen_height / 2), glm::vec2(10.0f, init_screen_height / 2));
		player_range_p[1] = std::make_unique<MoveObj>("Player_Range", glm::vec2(init_screen_width, init_screen_height / 2), glm::vec2(10.0f, init_screen_height / 2));
		player_range_p[2] = std::make_unique<MoveObj>("Player_Range", glm::vec2(0.0f, init_screen_height / 2 - 10.0f), glm::vec2(init_screen_width, 10.0f));
		player_range_p[3] = std::make_unique<MoveObj>("Player_Range", glm::vec2(0.0f, init_screen_height), glm::vec2(init_screen_width, 10.0f));
		for (int i = 0; i < 4; i++)
			player_range_p[i]->log_collision();
	}
	is_init_range = true;
}
Player::~Player()
{
	detach_all();
}
void Player::log_all()
{
	log_renderer();
	log_keyboard();
	log_move();
	log_collision();
}

void Player::detach_all()
{
	detach_move();
	detach_keyboard();
	detach_collision();
	detach_renderer();
}
//TODO 更好的输入速度响应
static const float v = 550.0f;
static glm::vec2 input_v = glm::vec2(0.0f);
void Player::processInput(int key, int action)
{
	if (action == GLFW_PRESS)
		switch (key)
		{
		case GLFW_KEY_A:
			input_v.x += -1;
			break;
		case GLFW_KEY_D:
			input_v.x += 1;
			break;
		case GLFW_KEY_W:
			input_v.y += -1;
			break;
		case GLFW_KEY_S:
			input_v.y += 1;
			break;
		}
	else if (action == GLFW_RELEASE)
		switch (key)
		{
		case GLFW_KEY_A:
			input_v.x -= -1;
			break;
		case GLFW_KEY_D:
			input_v.x -= 1;
			break;
		case GLFW_KEY_W:
			input_v.y -= -1;
			break;
		case GLFW_KEY_S:
			input_v.y -= 1;
			break;
		}
	std::cout << key << "\t" << action << std::endl;
	if (input_v.x || input_v.y)
		velocity = glm::normalize(glm::vec2(input_v)) * v;
	else
		velocity = glm::vec2(0.0f);
}

void Player::do_collision(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
	pos += offset;
}
