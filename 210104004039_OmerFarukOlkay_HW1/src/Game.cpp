#include "../lib/Game.hpp"

Game::Game(Board &board): board(board)
{
}

void Game::gameMenu()
{
    std::string input;
    while (1)
    {
        std::cout << "\n\nWelcome to Chess\n" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Help" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        getline(std::cin, input);
        if (input == "1")
        {
            board.initBoard();
            gamePlay();
        }
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
    board.updateUnderAttack();
    // board.score();
    int turn = Board::getTurn();
    std::string input;
    while (board.isCheckmate(turn % 2) == 0)
    {
        input = inputFromUser(turn);
        if (input == "next move")
        {
            nextMove();
            board.updateUnderAttack();
            Board::setTurn(++turn);
            // board.score();
            std::cout << board << std::endl;
        }
        else if (input == "exit")
        {
            std::cout << "Going back to game menu\n";
            return ;
        }
        else if (input != "save" && input != "suggest" &&  board.checkInputFormat(input))
        {
            if (board.validateMove(input))
            {
                Piece tmp = board.getPiece(input[3]-'0'-1, input[2]-'a');
                if (board.movePiece(input[0]-'a', input[1]-'0'-1, input[2]-'a', input[3]-'0'-1) == 1)
                {
                    // board.updateUnderAttack();
                    if (board.isCheck(turn % 2) == true) {
                        board.undoMove(tmp, input[2]-'a', input[3]-'0'-1, input[0]-'a', input[1]-'0'-1);
                        std::cout << "Invalid move, your king is under attack\n";
                    }
                    else
                    {
                        Board::setTurn(++turn);
                        // board.score();
                        std::cout << board << std::endl;
                    }
                }
            }
        }
        saveToFile();
    }
    std::cout << "\n[Checkmate!!]\n";
    if (Board::getTurn() % 2 == 0)
        std::cout << "Black Won\n";
    else
        std::cout << "White Won\n";
}

void Game::help()
{
    std::cout << "\nUse the standard notation for moves, e.g. e2e4\n";
    std::cout << "Type 'save' to save the game to a file\n";
    std::cout << "Type 'exit' to exit the game\n";
    std::cout << "Type 'suggest' to get a suggestion\n";
    std::cout << "Type 'next move' to play best move\n\n";
}

void Game::suggestMove()
{
    std::string move = board.suggestMove(Board::getTurn() % 2);
    std::cout << "Suggested move: " << move << std::endl;
    
}

void Game::nextMove()
{
    std::string move = board.suggestMove(Board::getTurn() % 2);
    if (move.empty())
    {
        return ;
    }
    std::cout << "Next move: " << move << std::endl;
    int x = move[0] - 'a';
    int y = move[1] - '0' - 1;
    int newX = move[2] - 'a';
    int newY = move[3] - '0' - 1;
    board.movePiece(x , y, newX, newY);
}

int Game::saveToFile()
{
    std::string fileName = "save.txt"; 
    std::ofstream ofs;
    ofs.open(fileName);
    if (ofs.is_open())
    {
        for (int i = 7; i >= 0; --i)
        {
            for (int j = 0; j < 8 ; ++j)
            {
                ofs << board.getPiece(i, j).getType();
            }
            ofs << "\n";
        }
        ofs << (Board::getTurn()) % 2;
    }
    else
        return (0);
    ofs.close();
    return (1);
}

int Game::loadFromFile(std::string fileName)
{
    std::ifstream ifs;
    ifs.open(fileName);
    int turn;
    if (ifs.is_open())
    {
        ifs >> this->board;
        ifs >> turn;
        Board::setTurn(turn);
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
        return input;
    }
    else if (input == "suggest")
    {
        suggestMove();
    }
    return (input);
}
