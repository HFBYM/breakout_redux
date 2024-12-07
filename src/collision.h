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
    using FuncType = std::function<void(const mString &)>;
    struct CollisionData
    {
        glm::vec2& pos;
        glm::vec2& size;
        FuncType func;
        CollisionData(glm::vec2& pos, glm::vec2& size, FuncType func):
            pos(pos), size(size), func(func){}
    };
    static Logger<CollisionData> logger;

    static void collision();

    /// @brief it can't be cleared twice
    static void clear();

};
