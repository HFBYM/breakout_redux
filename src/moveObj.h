#pragma once
#include"object.h"
class MoveObj:virtual public Object
{
protected:
    bool is_log_move = false;
    glm::vec2 velocity = glm::vec2(0.0f);
    glm::vec2 accelerate = glm::vec2(0.0f);
    
public:
    /// @brief this constructor is used to create its derived class
    MoveObj(glm::vec2 v = glm::vec2(0.0f)):velocity(v),Object("MoveObj"){}

    /// @brief this constructor is used to create independent MoveObj
    MoveObj(const mString& id_name, const glm::vec2& pos, const glm::vec2& size):Object(pos,size,id_name){}
    ~MoveObj();

    void log_move();
    void detach_move();
};
