#pragma once
#include"renderObj.h"
#include"moveObj.h"
#include"collisionObj.h"
class Ball:public RenderObj,public MoveObj,public CollisionObj
{
private:
    float radius =0.0f;
    unsigned int screen_width = 0;
    unsigned int screen_height = 0;
public:
    Ball(unsigned int screen_width, unsigned int screen_height, glm::vec3 color = glm::vec3(1.0f), float radius = 25.0f);
    ~Ball() = default;

    virtual void log_all();
    virtual void detach_all();

    /// @brief it requries the player position and size to set the ball position
    void setPos(const glm::vec2& player_pos, const glm::vec2& player_size);
};
