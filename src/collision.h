#pragma once
#include<functional>
#include"logger.h"
#include"glm.hpp"
class Collision
{
private:
    Collision() = delete;
    ~Collision() = delete;
public:
    using FuncType = std::function<void(const mString& message, const glm::vec2& reflect, const glm::vec2& offset)>;
    struct CollisionData
    {
        glm::vec2& pos;
        glm::vec2& size;
        const glm::vec2 &velocity;
        FuncType func;
        CollisionData(glm::vec2& pos, glm::vec2& size, FuncType func, const glm::vec2 &velocity):
            pos(pos), size(size), func(func), velocity(velocity){}
    };
    static Logger<CollisionData> logger;

    static void collision(float dt);

    /// @brief it can't be cleared twice
    static void clear();
};
