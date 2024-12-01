#include"brick.h"
#include"renderer.h"
#include"check.h"
static unsigned int s_id_num = 0;
static mString shader_name = "sprite";
Brick::Brick(const glm::vec2& pos, const glm::vec2& size, const mString& tex, BrickType type,
	bool isSolid, glm::vec3 color):
	Object(pos, size, "Brick", 0), type(type), color(color), tex(tex),isSolid(isSolid)
{
	this->id_num = s_id_num++;
}

Brick::~Brick()
{
	ASSERT_LOG(!is_log_renderer, "ERROR::BRICK: Brick" << id_num << "isn't detached all");
}

void Brick::log_renderer()
{
	if(!is_log_renderer)
		Renderer::log(id_name, id_num, shader_name, tex, pos, size_draw, rotate, color);
	is_log_renderer = true;
}

void Brick::detach_renderer()
{
	if(is_log_renderer)
		Renderer::detach(id_name, id_num);
	is_log_renderer = false;
}

void Brick::log_all()
{
	log_renderer();
}

void Brick::detach_all()
{
	detach_renderer();
}
