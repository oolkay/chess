#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include <vector>
#include <string>
#include <fstream>

const int WHITE = 0;
const int BLACK = 1;

class Board{
    public:
        Board();
        ~Board();
        Board(const Board& other);
        Board& operator=(const Board& other);

        //<<, >> OPERATOR OVERLOADS
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        friend std::istream& operator>>(std::istream& is, Board& board);


        //VALIDATION OF INPUT AND MOVE
        bool checkInputFormat(const std::string& input) const;
        bool validateMove(const std::string& input);
        bool validatePawnMove(int oldX, int oldY, int newX, int newY) const;
        bool validateRookMove(int oldX, int oldY, int newX, int newY) const;
        bool validateBishopMove(int oldX, int oldY, int newX, int newY) const;
        bool validateKnightMove(int oldX, int oldY, int newX, int newY) const;
        bool validateKingMove(int oldX, int oldY, int newX, int newY) const;
        bool isTherePiece(int x, int y) const;
        int movePiece(int oldX, int oldY, int newX, int newY);
        void undoMove(const Piece& oldPiece, int oldX, int oldY, int newX, int newY);


        //CHECKMATE, CHECK
        bool saveTheKingFromRook(const Piece& king, const Piece& rook);
        bool saveTheKingFromBishop(const Piece& king, const Piece& bishop);
        bool isCheckmate(int color);
        bool isWhiteCheck();
        bool isCheck(int color);
        bool isBlackCheck();
        Piece& getKing(int color);
        bool checkAllDefenders(const Piece& p);
        bool checkAnyPawnDefendsRook(int coordX, const Piece& king);
        bool checkAnyPawnDefendsBishop(int coordX, int coordY, const Piece& king);

        //SCORE, THREATS
        void isPawnAttacks(const Piece& p) ;
        void isRookAttacks(const Piece& p);
        void isBishopAttacks(const Piece& p);
        void isKnightAttacks(const Piece& p);
        void isKingAttacks(const Piece& p);
        void isQueenAttacks(const Piece& p);
        void updateUnderAttack();
        void score();

        inline static int getTurn() { return turn;};
        inline Piece getPiece(int y, int x) { return board[y][x];};
        static void setTurn(int turn);


    private:
        std::vector< std::vector<Piece> > board;
        static int turn;
        // std::vector<Piece> whiteP;
        // std::vector<Piece> blackP;
};

#endif