/**
 * @file menu.cpp
 * @author: Clare  email: 1090535708@qq.com
 * @date 2025-03-14
 * @copyright Copyright (c) 2025 by Clare, All Rights Reserved.
 */
#include "game/menu.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <conio.h>

#include "engines/soundEngine.h"
namespace menu
{
    struct Menu::MenuData
    {
        MenuState state = MenuState::START_MENU;
        int selectedIndex = 0;
        int preIndex = -1;
        const int arrow_width = 4;

        std::vector<std::string> start_menu = {"Singleplayer", "Multiplayer", "Exit"};
        std::vector<std::string> levels = {"Level 1", "Level 2", "Level 3", "Level 4",
                                           "Level 5", "Back to start menu"};
        std::function<void(int, int)> onGame;
        explicit MenuData(std::function<void(int, int)> onGame) : onGame(onGame) {}
    };
    namespace
    {
        void setColor(Menu::ConsoleColor color)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
        }

        void hideCursor()
        {
            CONSOLE_CURSOR_INFO cursorInfo;
            cursorInfo.dwSize = 1;
            cursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        }

        /// @brief get the console size
        /// @return first is the width and second is the height
        std::pair<int, int> getConsoleSize()
        {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            return std::make_pair(csbi.srWindow.Right - csbi.srWindow.Left + 1,
                                  csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
        }
    } // namespace
    void Menu::setCursorPos(int x, int y)
    {
        COORD coord = {(SHORT)x, (SHORT)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    Menu::Menu(std::function<void(int, int)> onGame) : data(std::make_unique<MenuData>(onGame))
    {
    }

    Menu::~Menu()
    {
    }
    void Menu::run()
    {
        hideCursor();
        int start_menu_choice = 0;
        std::function<void()> enter_start_menu = [&]
        {
            start_menu_choice = data->selectedIndex;
            switch (data->selectedIndex)
            {
            case 0:
                data->preIndex = -1;
                data->state = MenuState::LEVEL_SELECT;
                break;
            case 1:
                data->preIndex = -1;
                data->state = MenuState::LEVEL_SELECT;
                break;
            case 2:
                system("cls");
                exit(0);
            default:
                break;
            }
            data->selectedIndex = 0;
        };
        std::function<void()> enter_level_select = [&]
        {
            if (data->selectedIndex == static_cast<int>(data->levels.size()) - 1)
            {
                data->preIndex = -1;
                data->state = MenuState::START_MENU;
                data->selectedIndex = 0;
                return;
            }
            data->state = MenuState::IN_GAME;
        };
        while (true)
        {
            switch (data->state)
            {
            case MenuState::START_MENU:
                draw(data->start_menu, "Main Menu");
                processInput(static_cast<int>(data->start_menu.size()), enter_start_menu);
                break;
            case MenuState::LEVEL_SELECT:
                draw(data->levels, "Level Select");
                processInput(static_cast<int>(data->levels.size()), enter_level_select);
                break;
            case MenuState::IN_GAME:
                system("cls");
                std::cout << "on game..." << std::endl;
                data->onGame(start_menu_choice, data->selectedIndex);
                data->state = MenuState::START_MENU;
                data->preIndex = -1;
                data->selectedIndex = 0;
                system("pause");
                break;
            }
        }
    }

    void Menu::draw(const std::vector<std::string> &items, const std::string &title)
    {
        auto console = getConsoleSize();
        static auto calculateX = [&](int length) -> int
        {
            return static_cast<int>((console.first - data->arrow_width - length) / 2.0f);
        };

        // calculate Y position
        int startY = (console.second - static_cast<int>(items.size())) / 2;

        // first draw
        if (data->preIndex == -1)
        {
            system("cls");

            // calculate title position
            int titleX = calculateX(static_cast<int>(title.length()));
            setCursorPos(titleX, 2);
            setColor(Menu::ConsoleColor::HIGHLIGHT);
            std::cout << "[ " << title << " ]";

            for (unsigned int i = 0; i < static_cast<unsigned int>(items.size()); ++i)
            {
                int xPos = calculateX(static_cast<int>(items[i].length()));
                setCursorPos(xPos, startY + static_cast<int>(i));

                if (i == data->selectedIndex)
                {
                    setColor(Menu::ConsoleColor::HIGHLIGHT);
                    std::cout << "> " << items[i] << " <";
                    setColor(Menu::ConsoleColor::DEFAULT);
                }
                else
                {
                    std::cout << "  " << items[i] << "  ";
                }
            }
        }
        else if (data->preIndex != data->selectedIndex)
        {
            // clear the previous line
            int xPos = calculateX(static_cast<int>(items[data->preIndex].length()));
            setCursorPos(xPos, startY + data->preIndex);
            std::cout << "  " << items[data->preIndex] << "  ";

            // draw the new line
            xPos = calculateX(static_cast<int>(items[data->selectedIndex].length()));
            setCursorPos(xPos, startY + data->selectedIndex);
            setColor(Menu::ConsoleColor::HIGHLIGHT);
            std::cout << "> " << items[data->selectedIndex] << " <";
            setColor(Menu::ConsoleColor::DEFAULT);
        }
        data->preIndex = data->selectedIndex;
    }

    void Menu::processInput(int item_num, std::function<void()> enter)
    {
        using sound_engine::SoundEngine;
        while (true)
        {
            if (_kbhit())
            {
                int key = _getch();

                // process direction keys
                if (key == 224)
                {
                    // direction keys should be called twice
                    key = _getch();

                    // up
                    if (key == 72)
                    {
                        SoundEngine::instance().play_music("BLEEPWAV");
                        data->selectedIndex = (data->selectedIndex - 1 + item_num) % item_num;
                        return;
                    }

                    // down
                    else if (key == 80)
                    {
                        SoundEngine::instance().play_music("BLEEPWAV");
                        data->selectedIndex = (data->selectedIndex + 1) % item_num;
                        return;
                    }
                }
                // Enter
                else if (key == 13)
                {
                    SoundEngine::instance().play_music("BLEEPMP3");
                    enter();
                    return;
                }
                else if (key == 27)
                {
                    system("cls");
                    exit(EXIT_SUCCESS);
                }
            }
            // decrease times to check
            Sleep(50);
        }
    }
} // namespace menu
