#pragma once
#include <functional>
#include "logger.h"
#include "glm.hpp"
struct CollisionData
{
public:
    using FuncType = std::function<void(const mString &message, const glm::vec2 &reflect, const glm::vec2 &offset)>;

    glm::vec2 &pos;
    glm::vec2 &size;
    const glm::vec2 &velocity;
    FuncType func;
    CollisionData(glm::vec2 &pos, glm::vec2 &size, FuncType func, const glm::vec2 &velocity) : pos(pos), size(size), func(func), velocity(velocity) {}
};

class Collision : public Logger<CollisionData>
{
private:
    Collision() = default;
    ~Collision() = default;

public:
    using Data = CollisionData;
    using FuncType = Data::FuncType;

    void collision(float dt);
    static Collision &instance()
    {
        static Collision instance;
        return instance;
    }
};
