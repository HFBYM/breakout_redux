#pragma once
#include "glm.hpp"
#include "logger.h"
struct MovementData
{
    glm::vec2 &pos;
    glm::vec2 &volecity;
    glm::vec3 &accelerate;
    MovementData(glm::vec2 &pos, glm::vec2 &volecity, glm::vec3 &accelerate) : pos(pos), volecity(volecity), accelerate(accelerate) {}
};

class Movement:public Logger<MovementData>
{
private:
    ~Movement() = default;
    Movement() = default;

public:
    using Data = MovementData;
    void move(float dt);

    static Movement& instance()
    {
        static Movement instance;
        return instance;
    }
};
