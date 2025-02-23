/*
 * @Author: Clare 1090535708@qq.com
 * @Date: 2025-02-08 14:20:49
 * @LastEditTime: 2025-02-23 19:31:41
 * @FilePath: \breakout_redux\src\game\menu.h
 * Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#pragma once
#include <functional>
#include<memory>
#include<string>
#include<vector>
namespace menu
{
    class Menu
    {
    public:
        enum class ConsoleColor
        {
            DEFAULT = 7,
            HIGHLIGHT = 12
        };
        enum class MenuState
        {
            START_MENU,
            LEVEL_SELECT,
            IN_GAME
        };
        explicit Menu(std::function<void(int, int)> onGame);
        ~Menu();
        void run();
        static void setCursorPos(int x, int y);

    private:
        struct MenuData;
        std::unique_ptr<MenuData> data;

        void draw(const std::vector<std::string> &items, const std::string &title);
        void processInput(int item_num, std::function<void()> enter);
    };
} // namespace menu
