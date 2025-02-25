/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:54:22
 * @FilePath: \breakout_redux\src\engines\renderer.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#include "engines/renderer.h"

#include <glad.h>

#include <string>
#include <memory>

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "resource_manage/resource_manager.h"
#include "utils/shader.h"
#include "utils/texture.h"
namespace render
{
    Renderer::Renderer()
    {
        // the leftup is origin after turning up and down
        GLfloat vertices[] = {
            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f, // 0
            1.0f, 0.0f, 1.0f, 0.0f, // 1
            0.0f, 0.0f, 0.0f, 0.0f, // 2
            1.0f, 1.0f, 1.0f, 1.0f, // 3
        };

        // caution the face cull
        GLuint indices[] = {
            0, 1, 2,
            0, 3, 1};
        GLuint vb;
        GLuint eb;
        glGenVertexArrays(1, &va);
        glGenBuffers(1, &vb);
        glGenBuffers(1, &eb);

        // bind the va first
        glBindVertexArray(va);

        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // enable the vertex attribute
        glEnableVertexAttribArray(0);

        // four float for one vertex
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
                              4 * sizeof(GLfloat), static_cast<GLvoid *>(0));

        // finish binding
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Renderer::~Renderer()
    {
        glDeleteVertexArrays(1, &va);
    }
    namespace
    {
        void draw(unsigned int va, const RendererData &data,
                  unsigned int width, unsigned int height)
        {
            using resource_manager::ResourceManager;
            ResourceManager &resource_manager = ResourceManager::instance();
            resource_manager.getShader(data.shader_name).use();

            // first move, then rotate, scale at last
            glm::mat4 model;
            model = glm::translate(model, glm::vec3(data.pos, 0.0f));

            // make it rotate to the middle
            model = glm::translate(model, glm::vec3(0.5 * data.size.x, 0.5 * data.size.y, 0.0f));

            // move it back
            model = glm::translate(model, glm::vec3(-0.5f * data.size.x,
                                                    -0.5f * data.size.y, 0.0f));

            model = glm::scale(model, glm::vec3(data.size, 1.0f));

            resource_manager.getShader(data.shader_name).setUniform("model", model);
            resource_manager.getShader(data.shader_name).setUniform("spriteColor", data.color);

            glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(width),
                                        static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
            resource_manager.getShader(data.shader_name).use().setUniform("image", 0);
            resource_manager.getShader(data.shader_name).use().setUniform("proj", proj);

            // bind the texture to slot 0
            glActiveTexture(GL_TEXTURE0);
            resource_manager.getTexture(data.texture_name).bind();
            glBindVertexArray(va);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
            glBindVertexArray(0);
        }
    } // namespace

    void Renderer::render(unsigned int width, unsigned int height)
    {
        // set the color to clear the color buffer and avoid overflowing
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        auto &data = getData();
        if (data.find("Background") != data.end())
            for (const auto &[_, background] : data.at("Background"))
                draw(va, *background, width, height);
        if (data.find("Brick") != data.end())
            for (const auto &[_, brick] : data.at("Brick"))
                draw(va, *brick, width, height);
        if (data.find("Brick_Solid") != data.end())
            for (const auto &[_, brick] : data.at("Brick_Solid"))
                draw(va, *brick, width, height);

        // using this function to enhance the color of the particle
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        if (data.find("Particle") != data.end())
            for (const auto &[_, particle] : data.at("Particle"))
                draw(va, *particle, width, height);

        // restore the blend function
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (data.find("Pad") != data.end())
            for (const auto &[_, pad] : data.at("Pad"))
                draw(va, *pad, width, height);
        if (data.find("Ball") != data.end())
            for (const auto &[_, ball] : data.at("Ball"))
                draw(va, *ball, width, height);
        if (data.find("Buff") != data.end())
            for (const auto &[_, buff] : data.at("Buff"))
                draw(va, *buff, width, height);
    }
} // namespace render
