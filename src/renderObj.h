#pragma once
#include"object.h"
class RenderObj:virtual public Object
{
protected:
	mString tex;
	mString shader;
	glm::vec4 color = glm::vec4(1.0f);
	bool is_log_renderer = false;
	float rotate = 0.0f;
public:

	/// @brief this let the RenderObj derived class have instance
	RenderObj(const mString& tex, const mString& shader, glm::vec4 color = glm::vec4(1.0f), float rotate = 0.0f) :
		color(color), tex(tex), shader(shader), rotate(rotate), Object("RenderObj") { }

    /// @brief this can let RenderObj have independent instance 
    RenderObj(const mString& id_name, const glm::vec2& pos, const glm::vec2& size, const mString& tex, 
		const mString& shader, glm::vec4 color = glm::vec4(1.0f), float rotate = 0.0f) :Object(pos, size, id_name),
		color(color), tex(tex), shader(shader), rotate(rotate){ }

	void Rotate() { static unsigned int i = 1; rotate += static_cast<float>(i) / 100.0f; }

    ~RenderObj();
		
	/// @brief user can log and detach any times
	void log_renderer();
	void detach_renderer();
};
