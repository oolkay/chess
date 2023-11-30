#include "../libraries/Board.hpp"

int main(void)
{
    Board board;
    std::cout << board << std::endl;
    board.score();
    while (1)
    {
        std::string input;
        if (board.getTurn() % 2 == 0)
            std::cout << "White's turn" << std::endl;
        else
            std::cout << "Black's turn" << std::endl;
        std::cout << "Enter move: ";
        getline(std::cin, input);
        if (board.checkInputFormat(input))
        {
            if (board.validateMove(input))
            {
                std::cout << board << std::endl;
                Board::setTurn(Board::getTurn() + 1);
                board.score();
            }
            else
                std::cout << "Invalid move" << std::endl;
        }
        else
            std::cout << "Invalid input" << std::endl;
    }
    return 0;
}