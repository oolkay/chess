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
            std::cout << "White's turn" << std::endl;
        else
            std::cout << "Black's turn" << std::endl;
        std::cout << "Enter move: ";
        getline(std::cin, input);
        if (board.checkInputFormat(input))
        {
            if (board.validateMove(input))
            {
                board.movePiece(input[0]-'a', input[1]-'0'-1, input[2]-'a', input[3]-'0'-1);
                board.updateUnderAttack();
                if (board.isCheck(turn % 2))
                {
                    board.movePiece(input[2]-'a', input[3]-'0'-1, input[0]-'a', input[1]-'0'-1);
                    board.updateUnderAttack();
                    std::cout << "It is check, you need to protect your king!\n";
                }
                else
                {
                    Board::setTurn(++turn);
                    board.score();
                    std::cout << board << std::endl;
                }
            }
            else
                std::cout << "Invalid move" << std::endl;
        }
        else
            std::cout << "Invalid input" << std::endl;
    }
    if (Board::getTurn() % 2 == 0)
        std::cout << "Black Won\n";
    else
        std::cout << "White Won\n";
    return 0;
}