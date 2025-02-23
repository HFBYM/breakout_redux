/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 11:24:04
 * @FilePath: \breakout_redux\src\obj_for_engines\renderObj.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <memory>
#include<string>
#include "objects/object.h"
namespace render_obj
{
	class RenderObj : virtual public object::Object
	{
	public:
		/// @brief this let the RenderObj derived class have instance
		RenderObj(const std::string &tex, const std::string &shader, const glm::vec4 &color);

		/// @brief this can let RenderObj have independent instance
		RenderObj(const std::string &id_name, const glm::vec2 &pos,
				  const glm::vec2 &size, const std::string &tex,
				  const std::string &shader, const glm::vec4 &color);
		~RenderObj();

		/// @brief user can log and detach any times
		void log_renderer();
		void detach_renderer();

	protected:
		void setColor(const glm::vec4 &color);
		const glm::vec4 &getColor() const;
		bool isLogRenderer() const;

	private:
		struct RenderObjData;
		std::unique_ptr<RenderObjData> data;

		void log_all() override { log_renderer(); }
		void detach_all() override { detach_renderer(); }
	};
} // namespace render_obj
