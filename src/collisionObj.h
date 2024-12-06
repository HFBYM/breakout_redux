#pragma once
#include"object.h"
class CollisionObj:virtual public Object
{
protected:
    bool is_log_collision = false;
public:
    /// @brief this let CollisionObj have instance of Object
    CollisionObj(const mString& id_name, const glm::vec2& pos, const glm::vec2& size):Object(pos,size,id_name){}

    /// @brief this let CollisionObj derived class have instance of Object
    CollisionObj():Object("CollisionObj") {}
    ~CollisionObj();

    void log_collision();
    void detach_collision();

    virtual void do_collision(const mString& message) {};
};
