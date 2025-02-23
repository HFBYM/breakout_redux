/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 13:24:57
 * @FilePath: \breakout_redux\src\obj_for_engines\renderObj.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "obj_for_engines/renderObj.h"

#include <string>
#include <memory>

#include "engines/renderer.h"
#include "renderObj.h"
namespace render_obj
{
	struct RenderObj::RenderObjData
	{
		std::string tex;
		std::string shader;
		glm::vec4 color;
		bool is_log_renderer = false;
		RenderObjData(const std::string &tex, const std::string &shader, const glm::vec4 &color)
			: tex(tex), shader(shader), color(color) {}
	};
	RenderObj::RenderObj(const std::string &tex, const std::string &shader, const glm::vec4 &color)
		: data(std::make_unique<RenderObjData>(tex, shader, color)),
		  Object(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), "RenderObj")
	{
	}
	RenderObj::RenderObj(const std::string &id_name, const glm::vec2 &pos,
						 const glm::vec2 &size, const std::string &tex, const std::string &shader,
						 const glm::vec4 &color)
		: Object(pos, size, id_name), data(std::make_unique<RenderObjData>(tex, shader, color)) {}

	RenderObj::~RenderObj()
	{
		detach_renderer();
	}

	void RenderObj::log_renderer()
	{
		using render::Renderer;
		if (!data->is_log_renderer)
			Renderer::instance().log(getIdName(), getIdNum(),
									 std::make_unique<render::RendererData>(data->shader, data->tex,
																			getPos(), getSize(), data->color));
		data->is_log_renderer = true;
	}

	void RenderObj::detach_renderer()
	{
		using render::Renderer;
		if (data->is_log_renderer)
			Renderer::instance().detach(getIdName(), getIdNum());
		data->is_log_renderer = false;
	}
	void RenderObj::setColor(const glm::vec4 &color)
	{
		data->color = color;
	}
	const glm::vec4 &RenderObj::getColor() const
	{
		return data->color;
	}
	bool RenderObj::isLogRenderer() const
	{
		return data->is_log_renderer;
	}
} // namespace render_obj
