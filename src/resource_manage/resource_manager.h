/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:41:11
 * @FilePath: \breakout_redux\src\resource_manage\resource_manager.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <memory>
#include <string>
#include <json.hpp>

#include "utils/texture.h"
#include "utils/shader.h"

namespace resource_manager
{
	/// @brief manager the shaders and textures and is a singleton
	class ResourceManager
	{
	private:
		using Shader = shader::Shader;
		using Texture2D = texture::Texture2D;

	public:
		using json = nlohmann::json;

		/// @brief open and read the files
		/// @param path file path
		/// @return by string
		std::string readFile(const std::string &path) const;

		const Shader &getShader(const std::string &name) const;
		const Texture2D &getTexture(const std::string &name) const;

		const json &getJsonData() const;

		static ResourceManager &instance()
		{
			static ResourceManager instance;
			return instance;
		}

	private:
		ResourceManager();
		~ResourceManager();

		/// @brief load texture2D from file
		/// @param file filepath
		/// @param has_alpha decides whether or not this texture has alpha channel
		/// @param name the texture name
		void loadTexture(const std::string &file, bool has_alpha, const std::string &name);

		void loadShader(const std::string &file, const std::string &name);

		struct ResourceData;
		std::unique_ptr<ResourceData> data;
	};
} // namespace resource_manager
