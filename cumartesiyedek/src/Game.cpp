#include "../libraries/Game.hpp"

Game::Game(Board &board): board(board)
{
}

void Game::gameMenu()
{
    std::string input;
    std::cout << "Welcome to Chess\n" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Help" << std::endl;
    std::cout << "4. Exit" << std::endl;
    while (1)
    {
        std::cout << "Enter your choice: ";
        getline(std::cin, input);
        if (input == "1")
            gamePlay();
        else if (input == "2")
        {
            std::cout << "Enter file name: ";
            getline(std::cin, input);
            if (loadFromFile(input))
            {
                std::cout << "Game loaded succesfully\n";
                gamePlay();
            }
            else
                std::cout << "File not found\n";
        }
        else if (input == "3")
            help();
        else if (input == "4")
        {
            std::cout << "Thank you for playing\n";
            exit(0);
        }
        else
        std::cout << "Invalid input\n";
    
    }
}

void Game::gamePlay()
{
    std::cout << "New Game Started\n";
    std::cout << "If you want to exit, enter exit\n";
    std::cout << "If you want to save, enter save\n";
    std::cout << board << std::endl;
    board.score();
    int turn = 0;
    std::string input;
    while (board.isCheckmate(turn % 2) == 0)
    {
        input = inputFromUser(turn);
        if (input != "save" && board.checkInputFormat(input))
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
}

void Game::help()
{
    std::cout << "\nUse the standard notation for moves, e.g. e2e4\n";
    std::cout << "Type 'save' to save the game to a file\n";
    std::cout << "Type 'exit' to exit the game\n\n";
}

int Game::saveToFile()
{
    std::string fileName;
    std::cout << "Enter file name: ";
    getline(std::cin, fileName);
    std::ofstream ofs;
    ofs.open(fileName);
    if (ofs.is_open())
        ofs << this->board;
    else
        return (0);
    ofs.close();
    return (1);
}

int Game::loadFromFile(std::string fileName)
{
    std::ifstream ifs;
    ifs.open(fileName);
    if (ifs.is_open())
    {
        ifs >> this->board;
    }
    else
        return (0);
    ifs.close();
    return (1);
}

std::string Game::inputFromUser(int turn)
{
    std::string input;
    if (turn % 2 == 0)
        std::cout << "\nWhite's turn\n" << std::endl;
    else
        std::cout << "\nBlack's turn\n" << std::endl;
    std::cout << "Enter move: ";
    getline(std::cin, input);
    if (input == "save")
    {
        if (saveToFile())
            std::cout << "Game saved succesfully\n";
        else
            std::cout << "Game not saved\n";
    }
    else if (input == "exit")
    {
        std::cout << "Thank you for playing\n";
        exit(0);
    }
    return (input);
}
