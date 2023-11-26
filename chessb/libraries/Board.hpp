#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include <vector>
#include <string>

class Board{
    public:
        Board();
        ~Board();
        Board(const Board& other);
        Board& operator=(const Board& other);
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        bool checkInputFormat(const std::string& input) const;
        bool validateMove(const std::string& input);
        bool validateWhitePawnMove(int oldX, int oldY, int newX, int newY) const;
        bool validateRookMove(int oldX, int oldY, int newX, int newY) const;
        bool validateBishopMove(int oldX, int oldY, int newX, int newY) const;
        bool validateKnightMove(int oldX, int oldY, int newX, int newY) const;

        bool isTherePiece(int x, int y) const;
        int move(const std::string& input);
        int moveWhitePawn(int oldX, int oldY, int newX, int newY);
        int moveRook(int oldX, int oldY, int newX, int newY);
        int moveBishop(int oldX, int oldY, int newX, int newY);
        int moveKnight(int oldX, int oldY, int newX, int newY);

    private:
        std::vector< std::vector<Piece> > board;
        static int turn;
        // std::vector<Piece> whiteP;
        // std::vector<Piece> blackP;
};

#endif