#pragma once
#include<vector>
#include<functional>
#include"mString.h"
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
    Menu(std::function<void(int, int)> onGame): onGame(onGame) {}
    ~Menu() = default;
    void run();
private:
    MenuState state = MenuState::START_MENU;
    int selectedIndex = 0;
    int preIndex = -1;
    const int arrow_width = 4;

    std::vector<mString> start_menu = { "Singleplayer", "Multiplayer", "Exit" };
    std::vector<mString> levels = { "Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Back to start menu" };
    std::function<void(int, int)> onGame;

    void draw(const std::vector<mString>& items, const mString& title);
    void processInput(int item_num, std::function<void()> enter);
};
