#include"renderObj.h"
#include"renderer.h"
#include"check.h"

RenderObj::~RenderObj()
{
	ASSERT_LOG(!is_log_renderer, "ERROR::RENDEROGJ: "<<id_name.getStr()<<" "
		<< id_num << "isn't detached in renderer");
}

void RenderObj::log_renderer()
{
	if (!is_log_renderer)
		Renderer::logger.log(id_name, id_num, Renderer::LogData{shader, tex, pos, size, rotate, color});
	is_log_renderer = true;
}

void RenderObj::detach_renderer()
{
	if (is_log_renderer)
		Renderer::logger.detach(id_name, id_num);
	is_log_renderer = false;
}
