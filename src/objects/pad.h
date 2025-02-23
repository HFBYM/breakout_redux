/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 13:32:14
 * @FilePath: \breakout_redux\src\objects\pad.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include <functional>
#include <memory>
#include<string>
#include "obj_for_engines/renderObj.h"
#include "obj_for_engines/moveObj.h"

namespace pad
{
	class Pad : public render_obj:: RenderObj, public move_obj:: MoveObj
	{
	public:
		enum class Key
		{
			LEFT = 0,
			RIGHT,
			UP,
			DOWN
		};

		Pad(const glm::vec2 &pos, std::function<void(unsigned int)> buff_process, glm::vec3 color);
		~Pad();

		void processInput(Key key, bool press);

		/// @brief reset the speed if true or increase the speed
		void speedup(bool reset);

		/// @brief reset the size if true or increase the size
		void sizeIncrease(bool reset);

		inline glm::vec2 getPos() { return Object::getPos(); }
		inline glm::vec2 getSize() { return Object::getSize(); }

		void setChaos(bool chaos);

		void setIcy(bool icy);

	private:
		struct PadData;
		std::unique_ptr<PadData> data;
		void log_all() override;
		void detach_all() override;

		void do_collision(const std::string &message,
			const glm::vec2 &reflect, const glm::vec2 &offset) override;
	};
} // namespace pad
