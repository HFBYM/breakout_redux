#pragma once
#include"glm.hpp"
#include"logger.h"
class Renderer
{
public:
struct LogData
{
    mString shader_name;
    mString texture_name;
    const glm::vec2& pos;       
    const glm::vec2& size;
    const float& rotate;
    const glm::vec3& color;
    LogData(const mString& shader_name, const mString& texture, const glm::vec2& pos, 
        const glm::vec2& size, float& rotate, const glm::vec3& color):shader_name(shader_name), 
        texture_name(texture), pos(pos), size(size), rotate(rotate), color(color){ }
};
private:
	Renderer() = delete;
	~Renderer() = delete;
public:
	static Logger<LogData> logger;

	static void init();
	static void render(unsigned int width, unsigned int height);
	static void clear();
};
