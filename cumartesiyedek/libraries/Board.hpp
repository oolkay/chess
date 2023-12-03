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

        //<<, >> OPERATOR OVERLOADS AND FILE OPERANDS
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        friend std::istream& operator>>(std::istream& is, Board& board);
        int loadFromFile(std::string fileName);
        int saveToFile(std::string fileName);
        

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
        void isPawnAttacks(Piece& p) ;
        void isRookAttacks(Piece& p);
        void isBishopAttacks(Piece& p);
        void isKnightAttacks(Piece& p);
        void isKingAttacks(Piece& p);
        void isQueenAttacks(Piece& p);
        void updateUnderAttack();

        void score();
        double  getScore(int color);
        std::string suggestMove(int color);

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