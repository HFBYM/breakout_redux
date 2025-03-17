/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-22 21:38:29
 * @FilePath: \breakout_redux\src\utils\shader.h
 * Copyright (c) 2025 by Clare, All Rights Reserved. 
 */
#pragma once
#include "utils/pch.h"
namespace shader{
class Shader
{
public:
    /// @brief a shader will be compiled after created
    Shader(const std::string &name,
        const std::string &vertexSource, const std::string &fragmentSouce);

    /// @brief it can't be copy constructed
    Shader(const Shader &) = delete;

    /// @brief copy is not allowed
    Shader &operator=(const Shader &other) = delete;

    /// @brief each shader should be clear manually
    ~Shader();

    /// @brief return *this and bind the shader
    const Shader &use() const;

    /// @brief if Uniform can't be found, program will break down.
    // after setting the uniform, the shader would be of use
    template <typename T>
    void setUniform(const std::string &name, const T &value) const;

private:
    struct ShaderData;
    std::unique_ptr<ShaderData> data;
    void checkCompileErrors(unsigned int object, const std::string &type) const;
};
} // namespace shader
