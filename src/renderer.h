#pragma once
#include<glm.hpp>

class Renderer
{
public:
	static void init();
	static void render();
	static void clear();

	/// @brief each varient logging will render using its params and it should detach before logging again
	static void log(const char* id_name, unsigned int id_num, const char* shader_name, 
		const char* texture, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color);

	static void detach(const char* id_name, unsigned int id_num);
private:
	Renderer() = delete;
	~Renderer() = delete;
	Renderer& operator=(Renderer&) = delete;
};
