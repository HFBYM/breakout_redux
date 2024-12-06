#pragma once
#include"mString.h"
#include"glm.hpp"
#include<functional>
class CollisionObj;
class Movement
{
private:
    ~Movement() = delete;
    Movement() = delete;
public:
    using FuncType = std::function<void(const mString &)>;

    static void log(const mString& id_type, unsigned int id_num, glm::vec2& pos, glm::vec2& volecity,
        glm::vec2& accelerate);
    static void detach(const mString& id_type, unsigned int id_num);

    static void log_collision(const mString& type, FuncType func, unsigned int id, glm::vec2& pos, glm::vec2& size);
    static void detach_collision(const mString& type, unsigned int id_num);
    
    static void move(float dt);
    static void collision();

    /// @brief it can't be cleared twice
    static void clear();
};
