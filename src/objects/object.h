/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 15:29:05
 * @FilePath: \breakout_redux\src\objects\object.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <string>
#include <glm.hpp>

namespace object
{
	/// @brief the base class for all objects and it's not a abstract class
	class Object
	{
	public:
		/// @brief by default the id_num will add up from 0
		Object(const glm::vec2 &pos, const glm::vec2 &size, const std::string &id_name)
			: pos(pos), size(size), id_name(id_name), id_num(getId_num()) {}

		/// @brief this is a special constructor for some class or object which has no size or pos
		explicit Object(const std::string &type) : id_name(type), id_num(getId_num()) {}

		virtual ~Object() = default;

		/// @brief this function will log all the attributes of the object
		void log() { log_all(); }

		/// @brief this function will detach all the attributes of the object
		void detach() { detach_all(); }

	protected:
		const glm::vec2 &getPos() { return pos; }
		const glm::vec2 &getSize() { return size; }
		const std::string &getIdName() { return id_name; }
		unsigned int getIdNum() { return id_num; }
		void setPos(const glm::vec2 &pos) { this->pos = pos; }
		void setSize(const glm::vec2 &size) { this->size = size; }

	private:
		/// @brief pos is the leftup point of the object
		glm::vec2 pos = glm::vec2(0.0f);

		glm::vec2 size = glm::vec2(0.0f);
		std::string id_name;
		unsigned int id_num = 0;

		virtual void log_all() = 0;
		virtual void detach_all() = 0;

		inline static unsigned int getId_num()
		{
			static unsigned int i = 0;
			return i++;
		}
	};
} // namespace object
