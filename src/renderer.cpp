#include"renderer.h"
#include"glad.h"
#include<map>
#include<iostream>
#include"resource_manager.h"
#include"shader.h"
#include"texture.h"
#include<gtc\type_ptr.hpp>
#include<gtc/matrix_transform.hpp>

#define CHECK_STATUS() if(!isInit){\
    std::cout << "ERROR::RENDERER: function "<<__FUNCTION__<<" uses renderer not initialized"\
    << std::endl;\
    __debugbreak();}\
    if(isClear){\
    std::cout << "ERROR::RENDERER: function "<<__FUNCTION__<<" uses renderer cleared" << std::endl;\
    __debugbreak();}

struct LogData
{
    const char* shader_name;
    const char* texture_name;
    glm::vec2 pos, size;
    float rotate;
    glm::vec3 color;
};

/// @brief there is only one va globally
static GLuint va;
static bool isInit = false, isClear = false;
static std::map<const char*, std::map<unsigned int, LogData>> log_datas;

void Renderer::init()
{
    isInit = true;
    // the leftup is origin after turning up and down
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,     //0
        1.0f, 0.0f, 1.0f, 0.0f,     //1
        0.0f, 0.0f, 0.0f, 0.0f,     //2
        1.0f, 1.0f, 1.0f, 1.0f,     //3
    };

    //caution the face cull
    GLuint indices[] = {
        0,1,2,
        0,3,1
    };
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
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    // finish binding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::render()
{
    CHECK_STATUS();
    for (auto& i : log_datas["Brick"])
    {
        LogData temp = i.second;
        ResourceManager::getShader(temp.shader_name).use();     //??”≈ªØ

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

        // bind the texture to slot 0
        glActiveTexture(GL_TEXTURE0);   
        ResourceManager::getTexture(temp.texture_name).bind();
        glBindVertexArray(va);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
    }
}

void Renderer::clear()
{
    CHECK_STATUS();
    isClear = true;
    glDeleteVertexArrays(1, &va);
    for (auto& i : log_datas)
        i.second.clear();
    log_datas.clear();
}

void Renderer::log(const char* id_name, unsigned int id_num, const char* shader_name,
    const char* texture, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color)
{
    CHECK_STATUS();
    log_datas[id_name][id_num] = { shader_name, texture, pos, size, rotate, color };
}

void Renderer::detach(const char* id_name, unsigned int id_num)
{
    CHECK_STATUS();
    log_datas[id_name].erase(id_num);
}
