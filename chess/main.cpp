#include "Board.hpp"


/*



*/
int main()
{
    Board board;
    board.printBoard();
    while (true)
    {
        std::string move;
        std::cout << "Enter your move: ";
        getline(std::cin, move);
        if (board.validateInputFormat(move))
            if (board.validateAndMove(move))
        board.printBoard();
        
    }
    return (0);
}