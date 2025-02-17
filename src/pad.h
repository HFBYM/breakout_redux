#pragma once
#include "renderObj.h"
#include "moveObj.h"
#include <functional>
class Pad : public RenderObj, public MoveObj
{
public:
	enum class Key
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

	Pad(const glm::vec2& pos, std::function<void(unsigned int)> buff_process, glm::vec3 color = glm::vec3(1.0f), glm::vec2 size = getInitSize());
	~Pad();

	void log_all() override;
	void detach_all() override;

	void processInput(Key key, bool press);
	void speedup(bool reset = false);
	void sizeIncrease(bool reset = false) { size.x = reset ? getInitSize().x : size.x + 25.0f; }

	inline glm::vec2 getPos() { return pos; }
	inline glm::vec2 getSize() { return size; }
	void setChaos(bool chaos) { isChaos = chaos; }
	void setIcy(bool icy) { isIcy = icy; accelerate = icy ? glm::vec4(1.0f) : glm::vec4(0.0f); }

private:
	/// @brief this call back function to process buff
	std::function<void(unsigned int)> buff_process;

	/// @brief the basic speed of the pad
	const float init_v = 550.0f;

	float v = init_v;

	/// @brief the basic acceleration of the pad
	float a = 2000.0f;

	/// @brief the input vector from user
	glm::vec2 input_v = glm::vec2(0.0f);

	bool isChaos = false;
	bool isIcy = false;

	inline static glm::vec2 getInitSize()
	{
		static glm::vec2 init_size(100.0, 20.0);
		return init_size;
	}
	void do_collision(const std::string &message, const glm::vec2 &reflect, const glm::vec2 &offset) override;
};
