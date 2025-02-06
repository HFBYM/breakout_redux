#include "pad.h"
#include <memory>

Pad::Pad(unsigned int width, unsigned int height, std::function<void(unsigned int)> buff_process, glm::vec3 color, glm::vec2 size)
	: RenderObj("paddle", "sprite", glm::vec4(color, 1.0f)), Object(glm::vec2((width - size.x) / 2, height - size.y), size, "Pad"), buff_process(buff_process)
{
}
Pad::~Pad()
{
	detach_all();
}
void Pad::log_all()
{
	log_renderer();
	log_move();
	log_collision();
}

void Pad::detach_all()
{
	detach_move();
	detach_collision();
	detach_renderer();
}
void Pad::processInput(Key key, bool press)
{
	if (press)
		switch (key)
		{
		case Key::LEFT:
			input_v.x += -1;
			break;
		case Key::RIGHT:
			input_v.x += 1;
			break;
		case Key::UP:
			input_v.y += -1;
			break;
		case Key::DOWN:
			input_v.y += 1;
			break;
		}
	else
		switch (key)
		{
		case Key::LEFT:
			input_v.x -= -1;
			break;
		case Key::RIGHT:
			input_v.x -= 1;
			break;
		case Key::UP:
			input_v.y -= -1;
			break;
		case Key::DOWN:
			input_v.y -= 1;
			break;
		}
	glm::vec2 temp_v;
	if (isChaos)
	{
		glm::vec2 temp = -input_v;
		if (temp.x || temp.y)
			temp_v = glm::normalize(temp) * v;
		else
			temp_v = glm::vec2(0.0f);
	}
	else
	{
		if (input_v.x || input_v.y)
			temp_v = glm::normalize(input_v) * v;
		else
			temp_v = glm::vec2(0.0f);
	}
	if (isIcy)
	{
		accelerate.x = temp_v.x / v * a;
		accelerate.y = temp_v.y / v * a;
	}
	else
		velocity = temp_v;
}

void Pad::do_collision(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
	pos += offset;
	if (message == "Buff")
	{
		buff_process(static_cast<unsigned int>(reflect.x));
	}
}
