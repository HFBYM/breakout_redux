/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 10:08:02
 * @FilePath: \breakout_redux\src\engines\movement.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved. 
 */

#include "engines/movement.h"

namespace movement{
void Movement::doMove(float dt)
{
	const auto& data = getData();
	for (const auto &[type, id_data] : data)
		for (const auto &[id, m_data] : id_data)
		{
			MovementData &temp = *m_data;
			if (temp.accelerate.z == 1.0f)
			{
				glm::vec2 temp_a;
				temp_a.x = temp.accelerate.x;
				temp_a.y = temp.accelerate.y;

				// this is the friction of the ground
				temp_a -= temp.volecity * 1.5f;

				temp.volecity += temp_a * dt;
				temp.pos += temp.volecity * dt;
			}
			else
			{
				temp.pos += temp.volecity * dt;
			}
		}
}
} // namespace movement
