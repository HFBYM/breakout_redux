#pragma once
class Shader
{
public:
    Shader(const char*name):m_name(name){}
    Shader& operator=(Shader&& other) = delete;

    /// @brief return *this and bind the shader
    Shader& use();

    /// @brief a shader must be compiled
    void compile(const char* vertexSource, const char* fragmentSouce);

    /// @brief delete the shader program which must be a compiled one.
    /// it can be recompile after clear but name can't change
    void clear();

    /// @brief if Uniform can't be found, program will break down.  
    //after setting the uniform, the shader would be of use
    template<typename T>
    void setUniform(const char* name, T& value);
private:    
    // the id of the shader
    unsigned int id = 0;

    bool is_compiled = false;
    const char* m_name = nullptr;

    void checkCompileErrors(unsigned int object, const char* type);
};
