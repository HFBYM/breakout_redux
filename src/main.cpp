#include"game.h"
int main()
{
    Game& breakout = Game::get_instance();
    breakout.run();
    return 0;
}