#include"renderObj.h"
#include"renderer.h"

RenderObj::~RenderObj()
{
	detach_renderer();
}

void RenderObj::log_renderer()
{
	if (!is_log_renderer)
		Renderer::instance().log(id_name, id_num, std::make_unique<Renderer::Data>(shader, tex, pos, size, rotate, color));
	is_log_renderer = true;
}

void RenderObj::detach_renderer()
{
	if (is_log_renderer)
		Renderer::instance().detach(id_name, id_num);
	is_log_renderer = false;
}
