#pragma once
#include"renderObj.h"
#include"keyboardObj.h"
#include"moveObj.h"
class Player : public RenderObj, public KeyboardObj, public MoveObj
{
public:
	Player(unsigned int width, unsigned int height, glm::vec3 color = glm::vec3(1.0f),
		   glm::vec2 size = getInitSize());
	~Player();

	virtual void log_all() override;
	virtual void detach_all() override;

	virtual void processInput(int key, int action) override;

    /// @brief control the range of the player
    virtual void do_collision(const mString& message, const glm::vec2& reflect, const glm::vec2& offset) override;

	inline glm::vec2 getPos() { return pos; }
	inline glm::vec2 getSize() { return size; }
private:
	unsigned int init_screen_width = 0;
	unsigned int init_screen_height = 0;
	
	// generate the player range object
	static std::unique_ptr<std::unique_ptr<MoveObj>[]> player_range_p;

	inline static glm::vec2 getInitSize() { static glm::vec2 init_size(100.0, 20.0); return init_size; }
};
