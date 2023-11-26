#include "../libraries/Board.hpp"

int main(void)
{
    Board board;
    std::cout << board << std::endl;
    while (1)
    {
        std::string input;
        std::cout << "Enter move: ";
        getline(std::cin, input);
        if (board.checkInputFormat(input))
        {
            if (board.validateMove(input))
            {
                std::cout << board << std::endl;
            }
            else
                std::cout << "Invalid move" << std::endl;
        }
        else
            std::cout << "Invalid input" << std::endl;
    }
    return 0;
}