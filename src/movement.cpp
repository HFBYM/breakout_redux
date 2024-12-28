#include"movement.h"

void Movement::move(float  dt)
{
	for(auto& [type, id_data]:data)
		for (auto& [id, m_data] : id_data)
		{
			Movement::Data& temp = *m_data;
			temp.volecity += temp.accelerate * dt;
			temp.pos += temp.volecity * dt;
		}
}