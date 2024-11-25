#include"game.h"
int main()
{
    Game& game = game.get_instance();
    game.init();
    game.run();

    return 0;
}