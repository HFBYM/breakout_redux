#pragma once
#include"mString.h"
#include"glm.hpp"
class CollisionObj;
class Movement
{
private:
    ~Movement() = delete;
    Movement() = delete;
public:
    static void log(const mString& id_type, unsigned int id_num, glm::vec2& pos, glm::vec2& volecity,
        glm::vec2& accelerate);
    static void detach(const mString& id_type, unsigned int id_num);

    static void log_collision(const mString& type, CollisionObj& obj, void(CollisionObj::* func_p)(const mString&), unsigned int id, glm::vec2& pos, glm::vec2& size);
    static void detach_collision(const mString& type, unsigned int id_num);
    static void work(float dt);
};
