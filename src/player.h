#pragma once
#include"renderObj.h"
#include"keyboardObj.h"
#include"moveObj.h"
#include"collisionObj.h"
class Player : public RenderObj, public KeyboardObj, public MoveObj
{
public:
	Player(unsigned int width, unsigned int height, glm::vec3 color = glm::vec3(1.0f), 
		glm::vec2 size = getInitSize());
	~Player();

	virtual void log_all();
	virtual void detach_all();

	virtual void processInput(int key, int action);
    //virtual void do_collision(const mString& message) {};
private:
	unsigned int init_screen_width = 0;
	unsigned int init_screen_height = 0;

	inline static glm::vec2 getInitSize() { static glm::vec2 init_size(100.0, 20.0); return init_size; }
};
