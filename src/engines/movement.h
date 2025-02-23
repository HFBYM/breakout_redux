/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 17:08:18
 * @FilePath: \breakout_redux\src\engines\movement.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include <glm.hpp>
#include "resource_manage/logger.h"
namespace movement
{
    struct MovementData
    {
        glm::vec2 &pos;
        glm::vec2 &volecity;
        glm::vec3 &accelerate;
        MovementData(glm::vec2 * pos, glm::vec2 *const volecity, glm::vec3 *const accelerate)
            : pos(*pos), volecity(*volecity), accelerate(*accelerate) {}
    };
    class Movement : public logger::Logger<MovementData>
    {
    private:
        ~Movement() = default;
        Movement() = default;

    public:
        void doMove(float dt);

        static Movement &instance()
        {
            static Movement instance;
            return instance;
        }
    };
} // namespace movement
