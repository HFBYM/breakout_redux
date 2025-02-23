/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:02:50
 * @FilePath: \breakout_redux\src\obj_for_engines\keyboardObj.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include "objects/object.h"
namespace keyboard_obj
{
    class KeyboardObj : virtual public object::Object
    {
    public:
        KeyboardObj();
        ~KeyboardObj();

        void log_keyboard();
        void detach_keyboard();
    protected:
        virtual void processInput(int key, int action) = 0;

    private:
        bool is_log_keyboard = false;

        void log_all() override { log_keyboard(); }
        void detach_all() override { detach_keyboard(); }
    };
} // namespace keyboard_obj
