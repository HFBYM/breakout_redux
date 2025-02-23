/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-12-26 15:32:38
 * @LastEditTime: 2025-02-23 15:32:57
 * @FilePath: \breakout_redux\src\objects\ball.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include <string>
#include <functional>
#include <memory>
#include "obj_for_engines/renderObj.h"
#include "obj_for_engines/moveObj.h"
namespace ball
{
    class Ball : public render_obj::RenderObj, public move_obj::MoveObj
    {
    public:
        /// @brief the ball need the pad position and size to set the ball position any time
        Ball(std::function<void(int)> player_add_score, const glm::vec3 &color);
        ~Ball();

        void processInput(int key, bool action);

        void setPos(const glm::vec2 &pad_pos, const glm::vec2 &pad_size,
                    unsigned int screen_width, unsigned int screen_height);
        void setSticked(bool sticked);
        void setThrough(bool through);
        void setColor(glm::vec3 color) { RenderObj::setColor({color, 1.0f}); }
        void resetColor();
        void setStealth(bool stealth);

    private:
        struct BallData;
        std::unique_ptr<BallData> data;

        void do_collision(const std::string &message,
            const glm::vec2 &reflect, const glm::vec2 &offset) override;
        void log_all() override;
        void detach_all() override;
    };
} // namespace ball
