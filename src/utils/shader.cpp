/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-22 21:55:07
 * @FilePath: \breakout_redux\src\utils\shader.cpp
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "utils/shader.h"

#include <glad.h>
#include <glfw3.h>

#include <tuple>
#include <regex>
#include <iterator>

#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "utils/debug.h"

namespace shader
{
    struct Shader::ShaderData
    {
        unsigned int id = 0;
        std::string m_name;
        std::map<std::string, bool> m_uniformList;

        explicit ShaderData(const std::string &name) : m_name(name) {}
    };
    Shader::Shader(const std::string &name,
                   const std::string &vertexSource, const std::string &fragmentSouce)
        : data(std::make_unique<ShaderData>(name))
    {
        // compile the vertex and fragment shader
        GLuint sVertex, sFragment;
        const char *temp_v = vertexSource.c_str();
        const char *temp_f = fragmentSouce.c_str();
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
            data->id = glCreateProgram();
            glAttachShader(data->id, sVertex);
            glAttachShader(data->id, sFragment);
            glLinkProgram(data->id);
            this->checkCompileErrors(data->id, "PROGRAM");
        }
        catch (std::tuple<std::string, std::string, std::string> &e)
        {
            std::cerr << std::get<0>(e) << std::endl;
            std::cerr << "name: " << data->m_name << "type: " << std::get<2>(e) << std::endl;
            std::cerr << std::get<1>(e) << std::endl;
            MDEBUG();
        }
        // program is created so these is out of use
        glDeleteShader(sVertex);
        glDeleteShader(sFragment);

        // get all uniform names
        std::vector<std::string> strs;
        strs.push_back(vertexSource);
        strs.push_back(fragmentSouce);
        for (const auto &str : strs)
        {
            std::regex pattern(R"(\bu_\S*\b)");

            std::sregex_iterator it(str.begin(), str.end(), pattern);
            std::sregex_iterator end;

            for (; it != end; ++it)
            {
                std::smatch match = *it;
                data->m_uniformList[match.str()] = false;
            }
        }
    }

    Shader::~Shader()
    {
        glDeleteProgram(data->id);
        data->id = 0;
    }

    const Shader &Shader::use() const
    {
        glUseProgram(data->id);
        return *this;
    }
    void Shader::checkUniformList() const
    {
        for (const auto &[name, value] : data->m_uniformList)
        {
            if (!value)
            {
                std::cerr << "ERROR::UNIFORM: uniform " << name << " not set in shader "
                << data->m_name << std::endl;
                __debugbreak();
            }
        }
    }
    void Shader::checkCompileErrors(unsigned int object, const std::string &type) const
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(object, 1024, NULL, infoLog);
                throw std::tuple<std::string, std::string, std::string>(
                    "ERROR::SHADER: compile_time error", infoLog, type);
            }
        }
        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, 1024, NULL, infoLog);
                throw std::tuple<std::string, std::string, std::string>(
                    "ERROR::PROGRAM: link_time error", infoLog, type);
            }
        }
    }

    template <typename T>
    void Shader::setUniform(const std::string &name, const T &value) const
    {
        int pos = glGetUniformLocation(this->data->id, name.c_str());
        try
        {
            if (pos == -1)
                throw std::runtime_error("ERROR::UNIFORM: unnamed uniform");
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
            std::cerr << "uniform name: " << name << std::endl;
            std::cerr << "shader name: " << data->m_name << std::endl;
            this->use();
            return;
        }
        data->m_uniformList[name] = true;
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
            static_assert(false, "ERROR::UNIFORM: type not supported");
        }
    }

    /// @brief need to instance the template
    template void Shader::setUniform<int>(const std::string &name, const int &value) const;
    template void Shader::setUniform<float>(const std::string &name,
                                            const float &value) const;
    template void Shader::setUniform<glm::vec2>(const std::string &name,
                                                const glm::vec2 &value) const;
    template void Shader::setUniform<glm::vec3>(const std::string &name,
                                                const glm::vec3 &value) const;
    template void Shader::setUniform<glm::vec4>(const std::string &name,
                                                const glm::vec4 &value) const;
    template void Shader::setUniform<glm::mat4>(const std::string &name,
                                                const glm::mat4 &value) const;
} // namespace shader
