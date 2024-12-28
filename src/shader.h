#pragma once
#include "mString.h"
// TODO 静态uniform
class Shader
{
public:
    /// @brief a shader will be compiled after created
    Shader(const mString &name, const mString &vertexSource, const mString &fragmentSouce);

    /// @brief it can't be copy constructed
    Shader(const Shader &) = delete;

    /// @brief copy is not allowed
    Shader &operator=(Shader &other) = delete;

    /// @brief each shader should be clear manually
    ~Shader();

    /// @brief return *this and bind the shader
    Shader &use();

    /// @brief if Uniform can't be found, program will break down.
    // after setting the uniform, the shader would be of use
    template <typename T>
    void setUniform(const mString &name, const T &value);

private:
    // the id of the shader
    unsigned int id = 0;

    mString m_name;

    void checkCompileErrors(unsigned int object, const mString &type);
};
