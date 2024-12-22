#pragma once
#include"renderObj.h"
#include"moveObj.h"
#include"keyboardObj.h"
class Ball:public RenderObj,public MoveObj, public KeyboardObj
{
private:
    float radius =0.0f;
    unsigned int screen_width = 0;
    unsigned int screen_height = 0;
    bool isSticked = true;
public:
    /// @brief the ball need the player position and size to set the ball position any time
    Ball(unsigned int screen_width, unsigned int screen_height, glm::vec3 color = glm::vec3(1.0f), float radius = 25.0f);

    ~Ball();

    virtual void log_all() override;
    virtual void detach_all() override;
    virtual void do_collision(const mString& message,const glm::vec2& reflect,const glm::vec2& offset) override;
    virtual void processInput(int key, int action) override;

    void setPos(const glm::vec2 &player_pos, const glm::vec2 &player_size);
};
