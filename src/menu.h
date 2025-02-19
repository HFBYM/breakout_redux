#pragma once
#include<vector>
#include<functional>
#include<string>
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
    static void setCursorPos(int x, int y);
private:
    MenuState state = MenuState::START_MENU;
    int selectedIndex = 0;
    int preIndex = -1;
    const int arrow_width = 4;

    std::vector<std::string> start_menu = { "Singleplayer", "Multiplayer", "Exit" };
    std::vector<std::string> levels = { "Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Back to start menu" };
    std::function<void(int, int)> onGame;

    void draw(const std::vector<std::string>& items, const std::string& title);
    void processInput(int item_num, std::function<void()> enter);
};
