#include"brick.h"
#include"renderer.h"

static unsigned int s_id_num = 0;
static const char* shader_name = "sprite";
Brick::Brick(glm::vec2 pos, glm::vec2 size, const char* tex, BrickType type, glm::vec3 color):
	Object(pos, size, "Brick", 0), type(type), color(color), tex(tex)
{
	this->id_num = s_id_num++;
}

Brick::~Brick()
{

}

void Brick::log_renderer()
{
	Renderer::log(id_name, id_num, shader_name, tex, pos, size_draw, rotate, color);
}

void Brick::detach_renderer()
{
	Renderer::detach(id_name, id_num);
}
