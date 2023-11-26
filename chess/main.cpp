#include "Board.hpp"


/*



*/
int main()
{
    Board board;
    std::cout << board;
    while (true)
    {
        std::string move;
        std::cout << "Enter your move: ";
        getline(std::cin, move);
        if (board.validateInputFormat(move))
        {

            if (board.validateAndMove(move))
                std::cout << board;
            else
                std::cout << "Invalid move" << std::endl;
        }
        else
        {
            std::cout << "Invalid move format" << std::endl;
        }
        
    }
    return (0);
}