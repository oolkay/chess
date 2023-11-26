# ifndef BOARD_HPP
#define BOARD_HPP

#include "Pieces.hpp"
#include <vector>
#include <iostream>

class Board
{
    public:
        Board();
        Board(const Board& rhs);
        Board& operator=(const Board& rhs);
        /*todo: << overlaod*/
        ~Board();
        void printBoard() const;
        void updateBoard(std::string move);
        bool validateInputFormat(std::string move) const;
        bool validateAndMove(std::string move);
        bool isTherePiece(std::string coord) const;
        int whichPiece(std::string coord) const;

    private:
        std::vector<Pieces> _wpieces;
        std::vector<Pieces> _bpieces;
        std::vector<std::vector<char>> _board;
};

# endif