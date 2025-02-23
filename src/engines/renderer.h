/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-22 23:54:05
 * @FilePath: \breakout_redux\src\engines\renderer.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include<string>

#include <glm.hpp>

#include "resource_manage/logger.h"

namespace render
{
    struct RendererData
    {
        const std::string shader_name;
        const std::string texture_name;
        const glm::vec2 &pos;
        const glm::vec2 &size;
        const glm::vec4 &color;
        RendererData(const std::string &shader_name, const std::string &texture,
                     const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color)
            : shader_name(shader_name), texture_name(texture), pos(pos), size(size), color(color) {}
        RendererData() = default;
    };
    class Renderer : public logger::Logger<RendererData>
    {
    public:
        static Renderer &instance()
        {
            static Renderer instance;
            return instance;
        }
        void render(unsigned int width, unsigned int height);

    private:
        Renderer();
        ~Renderer();

        unsigned int va = 0;
    };
} // namespace render
