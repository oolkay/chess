#include "../libraries/Board.hpp"

int main(void)
{
    Board board;
    std::ifstream ifs;
    ifs.open("board.txt");
    if (ifs.is_open())
        ifs >> board;
    else
        std::cout << "File not found" << std::endl;
    std::cout << board << std::endl;
    board.score();
    int turn = 0;
    while (board.isCheckmate(turn % 2) == 0)
    {
        std::string input;
        if (turn % 2 == 0)
            std::cout << "\nWhite's turn\n" << std::endl;
        else
            std::cout << "\nBlack's turn\n" << std::endl;
        std::cout << "Enter move: ";
        getline(std::cin, input);
        if (board.checkInputFormat(input))
        {
            if (board.validateMove(input))
            {
                if (board.movePiece(input[0]-'a', input[1]-'0'-1, input[2]-'a', input[3]-'0'-1) == 1)
                {
                    board.updateUnderAttack();
                    Board::setTurn(++turn);
                    board.score();
                    std::cout << board << std::endl;
                }
            }
        }
    }
    if (Board::getTurn() % 2 == 0)
        std::cout << "Black Won\n";
    else
        std::cout << "White Won\n";
    return 0;
}