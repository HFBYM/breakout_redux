#pragma once
#include"glm.hpp"
#include"logger.h"
#include<iostream>

struct RendererData
{
    std::string shader_name;
    std::string texture_name;
    const glm::vec2& pos;       
    const glm::vec2& size;
    const float& rotate;
    const glm::vec4& color;
    RendererData(const std::string& shader_name, const std::string& texture, const glm::vec2& pos, 
        const glm::vec2& size, float& rotate, const glm::vec4& color):shader_name(shader_name), 
        texture_name(texture), pos(pos), size(size), rotate(rotate), color(color){ }
};
class Renderer:public Logger<RendererData>
{
private:
	Renderer();
	~Renderer();

    unsigned int va = 0;

public:
    using Data = RendererData;

	void render(unsigned int width, unsigned int height);

    static Renderer& instance()
    {
        static Renderer instance;
        return instance;
    }
};
