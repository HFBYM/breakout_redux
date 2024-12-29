#include"brick.h"
#include<iostream>

void Brick::log_all()
{
	log_renderer();
	log_collision();
}

void Brick::detach_all()
{
	detach_renderer();
	detach_collision();
}

void Brick::do_collision(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)
{
	std::cout<<"Brick "<<this->id_num<<" collided with "<<message.getStr()<<std::endl;
	if(!isSolid)
		this->detach_all();
}
