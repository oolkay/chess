#include "../libraries/Game.hpp"

int main(void)
{
    Board board;
    Game game(board);
    game.gameMenu();
    return 0;
}