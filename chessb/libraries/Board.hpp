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
        bool validatePawnMove(int oldX, int oldY, int newX, int newY) const;
        bool validateRookMove(int oldX, int oldY, int newX, int newY) const;
        bool validateBishopMove(int oldX, int oldY, int newX, int newY) const;
        bool validateKnightMove(int oldX, int oldY, int newX, int newY) const;

        bool isTherePiece(int x, int y) const;
        int movePiece(int oldX, int oldY, int newX, int newY);
        inline static int getTurn() { return turn;};
        static void setTurn(int turn);
        void isPawnAttacks(const Piece& p) ;
        void isRookAttacks(const Piece& p);
        void isBishopAttacks(const Piece& p);
        void isKnightAttacks(const Piece& p);
        void isKingAttacks(const Piece& p);
        void isQueenAttacks(const Piece& p);
        void updateUnderAttack();
        void score();


    private:
        std::vector< std::vector<Piece> > board;
        static int turn;
        // std::vector<Piece> whiteP;
        // std::vector<Piece> blackP;
};

#endif