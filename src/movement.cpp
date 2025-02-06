#include "movement.h"

void Movement::move(float dt)
{
	for (auto &[type, id_data] : data)
		for (auto &[id, m_data] : id_data)
		{
			Movement::Data &temp = *m_data;
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
				temp.volecity.x += temp.accelerate.x * dt;	
				temp.volecity.y += temp.accelerate.y * dt;
				temp.pos += temp.volecity * dt;
			}
		}
}