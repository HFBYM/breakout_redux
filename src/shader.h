#pragma once
//libs for math
#include<glm.hpp>
#include<gtc\type_ptr.hpp>
#include<gtc/matrix_transform.hpp>
class Shader
{
public:
    Shader(const char*name):m_name(name){}

    /// @brief can't use a shader to construct another cause the id is uniqe
    Shader(Shader&) = delete;
    Shader& operator=(Shader&) = delete;

    /// @brief the right value could be use to assign
    Shader& operator=(Shader&& other) = default;
    Shader(Shader&&) = default;

    /// @brief return *this and bind the shader
    Shader& use();

    /// @brief a shader must be compiled
    void compile(const char* vertexSource, const char* fragmentSouce);

    /// @brief delete the shader program which must be a compiled one
    void clear();

    void setFloat(const char* name, float val, bool useShader = false);
    void setInteger(const char* name, int value, bool useShader = false);
    void setVector2f(const char* name, float x, float y, bool useShader = false);
    void setVector2f(const char* name, const glm::vec2& value, bool useShader = false);
    void setVector3f(const char* name, float x, float y, float z, bool useShader = false);
    void setVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void setVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void setVector4f(const char* name, const glm::vec4& value, bool useShader = false);
    void setMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
private:
    // the id of the shader
    unsigned int id = 0;

    bool is_compiled = false;
    const char* m_name = nullptr;

    void checkCompileErrors(unsigned int object, const char* type);
};