#pragma once
#include<functional>
#include"mString.h"
#include"glm.hpp"
class CollisionObj;
class Collision
{
private:
    Collision() = default;
    ~Collision() = default;
public:
    using FuncType = std::function<void(const mString &)>;
    static void log(const mString& type, FuncType func, unsigned int id, glm::vec2& pos, glm::vec2& size);
    static void detach(const mString& type, unsigned int id_num);

    static void collision();

    /// @brief it can't be cleared twice
    static void clear();

};
