/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 13:56:38
 * @FilePath: \breakout_redux\src\objects\pad.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "objects/pad.h"

#include <memory>
#include <string>

#include "engines/particle_generator.h"
namespace pad
{
	namespace
	{
		/// @brief the basic speed of the pad
		constexpr float init_v = 550.0f;

		const glm::vec2 init_size(100.0f, 20.0f);

		/// @brief the basic acceleration of the pad
		constexpr float a = 2000.0f;
	}
	struct Pad::PadData
	{
		/// @brief this call back function to process buff
		std::function<void(unsigned int)> buff_process;

		float v = init_v;

		/// @brief the input vector from user
		glm::vec2 input_v = glm::vec2(0.0f);

		bool isChaos = false;
		bool isIcy = false;
		explicit PadData(std::function<void(unsigned int)> buff_process) : buff_process(buff_process) {}
	};
	Pad::Pad(const glm::vec2 &pos, std::function<void(unsigned int)> buff_process, glm::vec3 color)
		: RenderObj("paddle", "sprite", glm::vec4(color, 1.0f)), MoveObj(glm::vec2(0.0f)),
		  Object(glm::vec2(pos.x - init_size.x / 2, pos.y - init_size.y), init_size, "Pad"),
		  data(std::make_unique<PadData>(buff_process))
	{
	}
	Pad::~Pad()
	{
		detach_move();
		detach_collision();
		detach_renderer();
	}
	void Pad::setIcy(bool icy)
	{
		data->isIcy = icy;
		setAcceleration(icy ? glm::vec4(1.0f) : glm::vec4(0.0f));
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
				data->input_v.x += -1;
				break;
			case Key::RIGHT:
				data->input_v.x += 1;
				break;
			case Key::UP:
				data->input_v.y += -1;
				break;
			case Key::DOWN:
				data->input_v.y += 1;
				break;
			}
		else
			switch (key)
			{
			case Key::LEFT:
				data->input_v.x -= -1;
				break;
			case Key::RIGHT:
				data->input_v.x -= 1;
				break;
			case Key::UP:
				data->input_v.y -= -1;
				break;
			case Key::DOWN:
				data->input_v.y -= 1;
				break;
			}
		glm::vec2 temp_v;
		if (data->isChaos)
		{
			glm::vec2 temp = -data->input_v;
			if (temp.x || temp.y)
				temp_v = glm::normalize(temp) * data->v;
			else
				temp_v = glm::vec2(0.0f);
		}
		else
		{
			if (data->input_v.x || data->input_v.y)
				temp_v = glm::normalize(data->input_v) * data->v;
			else
				temp_v = glm::vec2(0.0f);
		}
		if (data->isIcy)
		{
			auto temp = getAcceleration();
			temp.x = temp_v.x / data->v * a;
			temp.y = temp_v.y / data->v * a;
			setAcceleration(temp);
		}
		else
			setVelocity(temp_v);
	}

	void Pad::speedup(bool reset)
	{
		using particle_generator::ParticleGenerator;
		data->v = reset ? init_v : data->v * 1.2f;
		if (!reset)
		{
			ParticleGenerator::instance().log(getIdName(), getIdNum(),
											  std::make_unique<particle_generator::ParticleData>(getPos(),
																								 getVelocity(), getSize(),
																								 getColor(), true));
		}
	}
	void Pad::setChaos(bool chaos)
	{
		data->isChaos = chaos;
	}
	void Pad::sizeIncrease(bool reset)
	{
		auto x = reset ? init_size.x : getSize().x + 25.0f;
		setSize(glm::vec2(x, init_size.y));
	}
	void Pad::do_collision(const std::string &message,
						   const glm::vec2 &reflect, const glm::vec2 &offset)
	{
		auto temp = getPos();
		temp += offset;
		setPos(temp);
		if (message == "Buff")
		{
			data->buff_process(static_cast<unsigned int>(reflect.x));
		}
	}
} // namespace pad
