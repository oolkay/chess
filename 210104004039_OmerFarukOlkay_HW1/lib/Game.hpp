#ifndef GAME_HPP
# define GAME_HPP

#include <string>
#include "Board.hpp"

class Game
{
    public:
        Game(Board& board);
        void    gameMenu();
        void    gamePlay();
        void    help();
        void    suggestMove();
        void    nextMove();
        int     saveToFile();
        int     loadFromFile(std::string fileName);
        std::string inputFromUser(int turn);
    private:
        Board&  board;
};

#endif
