/***
 * @Author: Clare 1090535708@qq.com
 * @Date: 2024-11-24 11:40:13
 * @LastEditTime: 2025-02-22 15:35:10
 * @FilePath: \breakout_redux\src\main.cpp
 * @Description:
 * @Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "game/game.h"
int main()
{
    using game::Game;
    Game::get_instance().run();
    return 0;
}
