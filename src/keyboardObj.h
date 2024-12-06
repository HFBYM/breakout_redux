#pragma once
#include"object.h"
class KeyboardObj:virtual public Object
{
protected:
    bool is_log_keyboard = false;
public:
    KeyboardObj():Object("KeyboardObj"){}
    ~KeyboardObj();

    void log_keyboard();
    void detach_keyboard();
    virtual void processInput(int key, int action){};
};
