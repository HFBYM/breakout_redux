#include "Shader.h"
#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include"debug.h"

Shader::Shader(const mString &name, const mString &vertexSource, const mString &fragmentSouce)
    : m_name(name)
{
    // compile the vertex and fragment shader
    GLuint sVertex, sFragment;
    const char *temp_v = vertexSource.getStr();
    const char *temp_f = fragmentSouce.getStr();
    try
    {
        sVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(sVertex, 1, &temp_v, NULL);
        glCompileShader(sVertex);
        this->checkCompileErrors(sVertex, "VERTEX");

        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(sFragment, 1, &temp_f, NULL);
        glCompileShader(sFragment);
        this->checkCompileErrors(sFragment, "FRAGMENT");

        // link the shader program
        this->id = glCreateProgram();
        glAttachShader(this->id, sVertex);
        glAttachShader(this->id, sFragment);
        glLinkProgram(this->id);
        this->checkCompileErrors(this->id, "PROGRAM");
    }
    catch (std::tuple<mString, mString, mString> &e)
    {
        std::cerr << std::get<0>(e).getStr() << std::endl;
        std::cerr << "name: " << m_name.getStr() << "type: " << std::get<2>(e).getStr() << std::endl;
        std::cerr << std::get<1>(e).getStr() << std::endl;
        MDEBUG();
    }
    // program is created so these is out of use
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
    this->id = 0;
}

const Shader &Shader::use() const
{
    glUseProgram(this->id);
    return *this;
}
void Shader::checkCompileErrors(unsigned int object, const mString &type) const
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            throw std::tuple<mString, mString, mString>("ERROR::SHADER: compile_time error", infoLog, type);
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            throw std::tuple<mString, mString, mString>("ERROR::PROGRAM: link_time error", infoLog, type);
        }
    }
}

template <typename T>
void Shader::setUniform(const mString &name, const T &value) const
{
    int pos = glGetUniformLocation(this->id, name.getStr());
    try
    {
        if (pos == -1)
            throw std::runtime_error("ERROR::UNIFORM: unnamed uniform");
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "uniform name: " << name.getStr() << std::endl;
        std::cerr << "shader name: " << m_name.getStr() << std::endl;
        this->use();
        return;
    }
    if constexpr (std::is_same_v<T, float>)
    {
        this->use();
        glUniform1f(pos, value);
    }
    else if constexpr (std::is_same_v<T, int>)
    {
        this->use();
        glUniform1i(pos, value);
    }
    else if constexpr (std::is_same_v<T, glm::vec2>)
    {
        this->use();
        glUniform2f(pos, value.x, value.y);
    }
    else if constexpr (std::is_same_v<T, glm::vec3>)
    {
        this->use();
        glUniform3f(pos, value.x, value.y, value.z);
    }
    else if constexpr (std::is_same_v<T, glm::vec4>)
    {
        this->use();
        glUniform4f(pos, value.x, value.y, value.z, value.w);
    }
    else if constexpr (std::is_same_v<T, glm::mat4>)
    {
        this->use();
        glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(value));
    }
    else
    {
        try
        {
            throw std::runtime_error("ERROR::UNIFORM: wrong type of value");
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
            std::cerr << "uniform name: " << name.getStr() << std::endl;
            std::cerr << "shader name: " << m_name.getStr() << std::endl;
            this->use();
            return;
        }
    }
}

/// @brief need to instance the template
template void Shader::setUniform<int>(const mString &name, const int &value) const;
template void Shader::setUniform<float>(const mString &name, const float &value) const;
template void Shader::setUniform<glm::vec2>(const mString &name, const glm::vec2 &value) const;
template void Shader::setUniform<glm::vec3>(const mString &name, const glm::vec3 &value) const;
template void Shader::setUniform<glm::vec4>(const mString &name, const glm::vec4 &value) const;
template void Shader::setUniform<glm::mat4>(const mString &name, const glm::mat4 &value) const;