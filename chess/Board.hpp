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
        ~Board();
        friend std::ostream& operator<<(std::ostream& os, const Board& rhs);
        void printBoard() const;
        void updateBoard(std::string move);
        bool validateInputFormat(std::string move) const;
        bool validateAndMove(std::string move) ;
        int  isTherePiece(std::string coord) const;
        bool ValidatePawnMove(const std::string& move) const;
        bool ValidateKnightMove(const std::string& move) const;
        bool ValidateBishopMove(const std::string& move) const;
        bool ValidateRookMove(const std::string& move) const;
        bool ValidateQueenMove(const std::string& move) const;
        bool ValidateKingMove(const std::string& move) const;
        int whichPiece(std::string coord) const;

    private:
        std::vector<Pieces> _wpieces;
        std::vector<Pieces> _bpieces;
        std::vector<std::vector<char> > _board;
};

# endif