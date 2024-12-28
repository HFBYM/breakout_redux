#pragma once
#include"glm.hpp"
#include"logger.h"
#include<iostream>

struct RendererData
{
    mString shader_name;
    mString texture_name;
    const glm::vec2& pos;       
    const glm::vec2& size;
    const float& rotate;
    const glm::vec3& color;
    RendererData(const mString& shader_name, const mString& texture, const glm::vec2& pos, 
        const glm::vec2& size, float& rotate, const glm::vec3& color):shader_name(shader_name), 
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

    inline void log(const mString &type, unsigned int id, std::unique_ptr<Data> value)
    {
        data[type][id] = std::move(value);
        data[type][id];
    }

    inline void detach(const mString &type, unsigned int id)
    {
        if(data.empty())
            return;
        data[type].erase(id);
    }

    static Renderer& instance()
    {
        static Renderer instance;
        return instance;
    }
};
