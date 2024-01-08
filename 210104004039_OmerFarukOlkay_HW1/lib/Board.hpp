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
        void initBoard();

        //<<, >> OPERATOR OVERLOADS AND FILE OPERANDS
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        friend std::istream& operator>>(std::istream& is, Board& board);
        

        //VALIDATION OF INPUT AND MOVE

        //checks if input is in correct format, e.g. a2a4
        bool checkInputFormat(const std::string& input) const;

        //checks if move is valid
        bool validateMove(const std::string& input) const;

        //checks if move is valid for a specific piece
        bool validatePawnMove(int oldX, int oldY, int newX, int newY) const;
        bool validateRookMove(int oldX, int oldY, int newX, int newY) const;
        bool validateBishopMove(int oldX, int oldY, int newX, int newY) const;
        bool validateKnightMove(int oldX, int oldY, int newX, int newY) const;
        bool validateKingMove(int oldX, int oldY, int newX, int newY) const;

        //checks if there is a piece on the way
        bool isTherePiece(int x, int y) const;

        //move and undo
        int  movePiece(int oldX, int oldY, int newX, int newY);
        void undoMove(const Piece& oldPiece, int oldX, int oldY, int newX, int newY);


        //CHECKMATE, CHECK
        bool isCheckmate(int color);
        bool isCheck(int color);
        Piece& getKing(int color);

        //SCORE, THREATS
        void isPawnAttacks(Piece& p) ;
        void isRookAttacks(Piece& p);
        void isBishopAttacks(Piece& p);
        void isKnightAttacks(Piece& p);
        void isKingAttacks(Piece& p);
        void isQueenAttacks(Piece& p);
        void updateUnderAttack();
        void setAndInsert(Piece& victimPiece , Piece& attackerPiece, int color);

        //SCORE, SUGGEST MOVE
        void        score();
        double      getScore(int color);
        std::string suggestMove(int color);

        inline static int getTurn() { return turn;};
        inline Piece getPiece(int y, int x) { return board[y][x];};
        static void setTurn(int turn);
        std::string intToString(int x, int y) const;


    private:
        std::vector< std::vector<Piece> > board;
        static int turn;
};

#endif