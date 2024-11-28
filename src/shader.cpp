#include"Shader.h"
#include<glad.h>	
#include<glfw3.h>	
#include<iostream>
#include<glm.hpp>
#include<gtc\type_ptr.hpp>
#include<gtc/matrix_transform.hpp>
// this is a micro to conveniently check if a shader is compiled
#define CHECK_COMPILE() if(!is_compiled){\
    std::cout << "ERROR::SHADER: function "<<__FUNCTION__<<" uses uncompiled shader "\
    << m_name << std::endl;\
    __debugbreak();}

Shader& Shader::use()
{
    CHECK_COMPILE();
    glUseProgram(this->id);
        return *this;
}
void Shader::checkCompileErrors(unsigned int object, const char* type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: compile_time error :type" << type << "name: " << m_name 
                << std::endl << infoLog << std::endl;
            __debugbreak();
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM: link_time error :type" << type << "name: " << m_name
                << std::endl << infoLog << std::endl;
            __debugbreak();
        }
    }
}
void Shader::compile(const char* vertexSource, const char* fragmentSouce)
{
    // compile the vertex and fragment shader
    GLuint sVertex, sFragment;
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL); 
    glCompileShader(sVertex);
    this->checkCompileErrors(sVertex, "VERTEX");

    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSouce, NULL);
    glCompileShader(sFragment);
    this->checkCompileErrors(sFragment, "FRAGMENT");

    //link the shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, sVertex);
    glAttachShader(this->id, sFragment);
    glLinkProgram(this->id);
    this->checkCompileErrors(this->id, "PROGRAM");

    //program is created so these is out of use
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);

    this->is_compiled = true;
}
void Shader::clear()
{
    CHECK_COMPILE();
    glDeleteProgram(this->id);
    this->id = 0;
    this->is_compiled = false;
}

template<typename T>
void Shader::setUniform(const char* name, T& value)
{
    CHECK_COMPILE();
    int pos = glGetUniformLocation(this->id, name);
    if (pos == -1)
    {
        std::cout << "ERROR::UNIFORM: " << name << " can't be found in " << this->m_name << std::endl;
        __debugbreak();
    }
    if constexpr (std::is_same_v<T, float>)
    {
        this->use();
        glUniform1f(glGetUniformLocation(this->id, name), value);

    }
    else if constexpr (std::is_same_v<T, int>)
    {
        this->use();
        glUniform1i(glGetUniformLocation(this->id, name), value);
    }
    else if constexpr (std::is_same_v<T, glm::vec2>)
    {
        this->use();
        glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
    }
    else if constexpr (std::is_same_v<T, glm::vec3>)
    {
        this->use();
        glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
    }
    else if constexpr (std::is_same_v<T, glm::vec4>)
    {
        this->use();
        glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
    }
    else if constexpr (std::is_same_v<T, glm::mat4>)
    {
        this->use();
        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }
    else
    {
        std::cout << "ERROR::UNIFORM: wrong type of value for " << name << " in " << this->m_name 
            << std::endl;
        __debugbreak();
    }
}