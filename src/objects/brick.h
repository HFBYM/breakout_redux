/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 13:25:42
 * @FilePath: \breakout_redux\src\objects\brick.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include <string>
#include <glm.hpp>
#include "obj_for_engines/renderObj.h"
#include "obj_for_engines/moveObj.h"
namespace brick
{
	class Brick : public render_obj::RenderObj, public move_obj::MoveObj
	{
	public:
		enum class BrickType
		{
			NONE = 0,
			SOLID,
			BLUE,
			GREEN,
			YELLOW,
			RED
		};

		Brick(const glm::vec2 &pos, const glm::vec2 &size, const std::string &tex,
			  BrickType type, bool isSolid, glm::vec3 color)
			: RenderObj(tex, "sprite", glm::vec4(color, 1.0f)), type(type), isSolid(isSolid),
			  MoveObj(glm::vec2(0.0f)), Object(pos, size, getName(isSolid)) {}

		/// @brief when a brick is distructed it should have cleaned all the logging
		~Brick() = default;

		bool isDestroyed() const { return !isLogRenderer(); }
		bool checkSolid() const { return isSolid; }

	private:
		BrickType type;

		bool isSolid = false;

		/// @brief when a brick is hit it should have cleaned all the logging and generate particles
		void do_collision(const std::string &message,
			const glm::vec2 &reflect, const glm::vec2 &offset) override;
		void log_all() override;
		void detach_all() override;
		std::string getName(bool isSolid) { return isSolid ? "Brick_Solid" : "Brick"; }
	};
} // namespace brick
