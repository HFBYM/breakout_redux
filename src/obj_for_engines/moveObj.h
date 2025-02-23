/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:39
 * @LastEditTime: 2025-02-23 13:49:24
 * @FilePath: \breakout_redux\src\obj_for_engines\moveObj.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include <memory>
#include <string>
#include <glm.hpp>
#include "objects/object.h"
namespace move_obj
{
    class MoveObj : virtual public object::Object
    {
    public:
        /// @brief this constructor is used to create its derived class
        explicit MoveObj(const glm::vec2 &v);

        /// @brief this constructor is used to create independent MoveObj
        MoveObj(const std::string &id_name, const glm::vec2 &pos, const glm::vec2 &size);
        ~MoveObj();

        void log_move();
        void detach_move();

        void log_collision();
        void detach_collision();

    protected:
        virtual void do_collision(const std::string &message,
                                  const glm::vec2 &reflect, const glm::vec2 &offset) {}
        void setVelocity(const glm::vec2 &velocity);
        const glm::vec2 &getVelocity() const;
        void setAcceleration(const glm::vec3 &acceleration);
        const glm::vec3 &getAcceleration() const;

    private:
        void log_all() override
        {
            log_move();
            log_collision();
        }

        void detach_all() override
        {
            detach_move();
            detach_collision();
        }
        struct MoveObjData;
        std::unique_ptr<MoveObjData> data;
    };
} // namespace move_obj
