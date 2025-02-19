#pragma once
#include <string>
class Shader
{
public:
    /// @brief a shader will be compiled after created
    Shader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSouce);

    /// @brief it can't be copy constructed
    Shader(const Shader &) = delete;

    /// @brief copy is not allowed
    Shader &operator=(Shader &other) = delete;

    /// @brief each shader should be clear manually
    ~Shader();

    /// @brief return *this and bind the shader
    const Shader &use() const;

    /// @brief if Uniform can't be found, program will break down.
    // after setting the uniform, the shader would be of use
    template <typename T>
    void setUniform(const std::string &name, const T &value) const;

private:
    // the id of the shader
    unsigned int id = 0;

    std::string m_name;

    void checkCompileErrors(unsigned int object, const std::string &type) const;
};
