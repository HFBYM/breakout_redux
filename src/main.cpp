#include"game.h"
#include<vector>
#include<iostream>
int main()
{
    Game& breakout = Game::get_instance();
    breakout.init();
    breakout.run();
    return 0;
}