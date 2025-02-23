/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-05 18:27:14
 * @LastEditTime: 2025-02-23 16:20:41
 * @FilePath: \breakout_redux\src\game\player.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include <memory>
#include "obj_for_engines/keyboardObj.h"
namespace player
{
    class Player : public keyboard_obj::KeyboardObj
    {
    public:
        enum class PlayerID
        {
            Player_Single,
            Player1,
            Player2
        };

        /// @brief the id should be unique globally
        Player(unsigned int screen_width, unsigned int screen_height, PlayerID player_id);
        ~Player();

        void update(float dt);

    private:
        struct PlayerData;
        std::unique_ptr<PlayerData> data;

        void log_all() override;
        void detach_all() override;

        void processInput(int key, int action) override;
        void buff_process(unsigned int id);
        void add_score(int value);
    };
} // namespace player
