#include "renderer.h"
#include "glad.h"
#include "resource_manager.h"
#include "shader.h"
#include "texture.h"
#include <gtc\type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

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
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);

    // finish binding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &va);
}

void Renderer::render(unsigned int width, unsigned int height)
{
    // set the color to clear the color buffer and avoid overflowing
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto &i : data["Brick"])
    {
        const RendererData &temp = *i.second;
        ResourceManager::getShader(temp.shader_name).use(); // TODO优化按照着色器分类

        // first move, then rotate, scale at last
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(temp.pos, 0.0f));

        // make it rotate to the middle
        model = glm::translate(model, glm::vec3(0.5 * temp.size.x, 0.5 * temp.size.y, 0.0f));
        model = glm::rotate(model, temp.rotate, glm::vec3(0.0f, 0.0f, 1.0f));

        // move it back
        model = glm::translate(model, glm::vec3(-0.5f * temp.size.x, -0.5f * temp.size.y, 0.0f));

        model = glm::scale(model, glm::vec3(temp.size, 1.0f));

        ResourceManager::getShader(temp.shader_name).setUniform("model", model);
        ResourceManager::getShader(temp.shader_name).setUniform("spriteColor", temp.color);

        glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(width),
                                    static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
        ResourceManager::getShader("sprite").use().setUniform("image", 0);
        ResourceManager::getShader("sprite").use().setUniform("proj", proj);

        // bind the texture to slot 0
        glActiveTexture(GL_TEXTURE0);
        ResourceManager::getTexture(temp.texture_name).bind();
        glBindVertexArray(va);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
    }
    for (const auto &i : data["Player"])
    {
        const RendererData &temp = *i.second;
        ResourceManager::getShader(temp.shader_name).use();

        // first move, then rotate, scale at last
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(temp.pos, 0.0f));

        // make it rotate to the middle
        model = glm::translate(model, glm::vec3(0.5 * temp.size.x, 0.5 * temp.size.y, 0.0f));
        model = glm::rotate(model, temp.rotate, glm::vec3(0.0f, 0.0f, 1.0f));

        // move it back
        model = glm::translate(model, glm::vec3(-0.5f * temp.size.x, -0.5f * temp.size.y, 0.0f));

        model = glm::scale(model, glm::vec3(temp.size, 1.0f));

        ResourceManager::getShader(temp.shader_name).setUniform("model", model);
        ResourceManager::getShader(temp.shader_name).setUniform("spriteColor", temp.color);

        glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(width),
                                    static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
        ResourceManager::getShader("sprite").use().setUniform("image", 0);
        ResourceManager::getShader("sprite").use().setUniform("proj", proj);

        // bind the texture to slot 0
        glActiveTexture(GL_TEXTURE0);
        ResourceManager::getTexture(temp.texture_name).bind();
        glBindVertexArray(va);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
    }
    for (const auto &i : data["Ball"])
    {
        const RendererData &temp = *i.second;
        ResourceManager::getShader(temp.shader_name).use();

        // first move, then rotate, scale at last
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(temp.pos, 0.0f));

        // make it rotate to the middle
        model = glm::translate(model, glm::vec3(0.5 * temp.size.x, 0.5 * temp.size.y, 0.0f));
        model = glm::rotate(model, temp.rotate, glm::vec3(0.0f, 0.0f, 1.0f));

        // move it back
        model = glm::translate(model, glm::vec3(-0.5f * temp.size.x, -0.5f * temp.size.y, 0.0f));

        model = glm::scale(model, glm::vec3(temp.size, 1.0f));

        ResourceManager::getShader(temp.shader_name).setUniform("model", model);
        ResourceManager::getShader(temp.shader_name).setUniform("spriteColor", temp.color);

        glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(width),
                                    static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
        ResourceManager::getShader("sprite").use().setUniform("image", 0);
        ResourceManager::getShader("sprite").use().setUniform("proj", proj);

        // bind the texture to slot 0
        glActiveTexture(GL_TEXTURE0);
        ResourceManager::getTexture(temp.texture_name).bind();
        glBindVertexArray(va);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
    }
}