#include "menu.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include"soundEngine.h"

static void setCursorPos(int x, int y)
{
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

static void setColor(Menu::ConsoleColor color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

static void hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/// @brief get the console size
/// @return first is the width and second is the height
static std::pair<int, int> getConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return std::make_pair(csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

void Menu::run()
{
    hideCursor();
    int start_menu_choice = 0;
    std::function<void()> enter_start_menu = [&]
    {
        start_menu_choice = selectedIndex;
        switch (selectedIndex)
        {
        case 0:
            preIndex = -1;
            state = MenuState::LEVEL_SELECT;
            break;
        case 1:
            preIndex = -1;
            state = MenuState::LEVEL_SELECT;
            break;
        case 2:
            system("cls");
            exit(0);
        default:
            break;
        }
        selectedIndex = 0;
    };
    std::function<void()> enter_level_select = [&]
    {
        if (selectedIndex == levels.size() - 1)
        {
            preIndex = -1;
            state = MenuState::START_MENU;
            selectedIndex = 0;
            return;
        }
        state = MenuState::IN_GAME;
    };
    while (true)
    {
        switch (state)
        {
        case MenuState::START_MENU:
            draw(start_menu, "Main Menu");
            processInput(static_cast<int>(start_menu.size()), enter_start_menu);
            break;
        case MenuState::LEVEL_SELECT:
            draw(levels, "Level Select");
            processInput(static_cast<int>(levels.size()), enter_level_select);
            break;
        case MenuState::IN_GAME:
            system("cls");
            std::cout << "loading..." << std::endl;
            onGame(start_menu_choice, selectedIndex);
            state = MenuState::START_MENU;
            preIndex = -1;
            selectedIndex = 0;
            break;
        }
    }
}

void Menu::draw(const std::vector<std::string> &items, const std::string &title)
{
    auto console = getConsoleSize();
    static auto calculateX = [&](unsigned int length) -> int
    { return static_cast<int>((console.first - arrow_width - static_cast<int>(length)) / 2.0f); };

    // calculate Y position
    int startY = (console.second - static_cast<int>(items.size())) / 2;

    // first draw
    if (preIndex == -1)
    {
        system("cls");

        // calculate title position
        int titleX = calculateX(title.length());
        setCursorPos(titleX, 2);
        setColor(Menu::ConsoleColor::HIGHLIGHT);
        std::cout << "[ " << title << " ]";

        for (unsigned int i = 0; i < items.size(); ++i)
        {
            int xPos = calculateX(items[i].length());
            setCursorPos(xPos, startY + static_cast<int>(i));

            if (i == selectedIndex)
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
    else if (preIndex != selectedIndex)
    {
        // clear the previous line
        int xPos = calculateX(items[preIndex].length());
        setCursorPos(xPos, startY + preIndex);
        std::cout << "  " << items[preIndex] << "  ";

        // draw the new line
        xPos = calculateX(items[selectedIndex].length());
        setCursorPos(xPos, startY + selectedIndex);
        setColor(Menu::ConsoleColor::HIGHLIGHT);
        std::cout << "> " << items[selectedIndex] << " <";
        setColor(Menu::ConsoleColor::DEFAULT);
    }
    preIndex = selectedIndex;
}

void Menu::processInput(int item_num, std::function<void()> enter)
{
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
                    SoundEngine::instance().play_music(SoundEngine::Song::BLEEPWAV);
                    selectedIndex = (selectedIndex - 1 + item_num) % item_num;
                    return;
                }

                // down
                else if (key == 80)
                {
                    SoundEngine::instance().play_music(SoundEngine::Song::BLEEPWAV);
                    selectedIndex = (selectedIndex + 1) % item_num;
                    return;
                }
            }
            // Enter键处理
            else if (key == 13)
            {
                SoundEngine::instance().play_music(SoundEngine::Song::BLEEPMP3);
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
