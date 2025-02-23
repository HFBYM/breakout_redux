/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 10:46:06
 * @FilePath: \breakout_redux\src\engines\collision.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */

#pragma once
#include<string>
#include<functional>
#include<glm.hpp>

#include "resource_manage/logger.h"
namespace collision
{
    struct CollisionData
    {
    public:
        using FuncType = std::function<void(const std::string &message,
                                            const glm::vec2 &reflect, const glm::vec2 &offset)>;

        const glm::vec2 &pos;
        const glm::vec2 &size;
        const glm::vec2 &velocity;
        FuncType func;
        CollisionData(const glm::vec2 &pos, const glm::vec2 &size, FuncType func,
                      const glm::vec2 &velocity)
            : pos(pos), size(size), func(func), velocity(velocity) {}
    };
    class Collision : public logger::Logger<CollisionData>
    {
    private:
        Collision() = default;
        ~Collision() = default;

    public:
        /// @brief access collision data and process
        void collision(float dt);
        static Collision &instance()
        {
            static Collision instance;
            return instance;
        }
    };
} // namespace collision
