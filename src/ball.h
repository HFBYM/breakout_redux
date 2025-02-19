#pragma once
#include "renderObj.h"
#include "moveObj.h"
#include <string>
#include<functional>
class Ball : public RenderObj, public MoveObj
{
private:
    float radius = 0.0f;
    bool isSticked = true;
    bool isThrough = false;
    glm::vec3 init_color;
    std::function<void(int)> player_add_score;

    void do_collision(const std::string &message, const glm::vec2 &reflect, const glm::vec2 &offset) override;

public:
    /// @brief the ball need the pad position and size to set the ball position any time
    Ball(std::function<void(int)> player_add_score, glm::vec3 color = glm::vec3(1.0f), float radius = 25.0f);

    ~Ball();

    void log_all() override;
    void detach_all() override;

    void processInput(int key, bool action);

    void setPos(const glm::vec2 &pad_pos, const glm::vec2 &pad_size);
    void setSticked(bool sticked) { isSticked = sticked; }
    void setThrough(bool through) { isThrough = through; }
    void setColor(glm::vec3 color) { this->color = glm::vec4(color, 1.0f); }
    void resetColor() { this->color = glm::vec4(init_color, color.a); }
    void setStealth(bool stealth);
};
