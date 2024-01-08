#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include <string>


class Piece {
    public:
        Piece();
        Piece(char _type, int color, int x, int y, int point);
        ~Piece();
        Piece(const Piece& other);
        Piece& operator=(const Piece& other);
        bool operator==(const Piece& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

        //GETTERS
        char            getType() const;
        int             getX() const;
        int             getY() const;
        bool            getIsUnderAttack(int color) const;
        inline bool     getIsUnderAttackByWhite() const { return this->isUnderAttackByWhite;};
        inline bool     getIsUnderAttackByBlack() const { return this->isUnderAttackByBlack;};
        inline Piece    getPieceAttacks(int i) const { return this->piecesAttacks[i];};
        inline std::vector<Piece> getAttackers() const { return this->piecesAttacks;};
        inline int      getPieceAttacksSize() const { return this->piecesAttacks.size();};
        inline int      getPossibleMovesSize() const { return this->possibleMoves.size();};
        inline std::string getPossibleMoves(int i) const { return this->possibleMoves[i];};
        int             getPoint() const;
        int             getColor() const;

        //SETTER
        void            setIsUnderAttack(int color, bool isUnderAttack);
        void            insertPiecesAttack(const Piece& p);
        void            insertPossibleMove(std::string move);
        void            setType(char type);
        void            setCoords(int x, int y);
        void            setCoords(std::string coords);
        void            setIsUnderAttackByWhite(bool isUnderAttackByWhite);
        void            setIsUnderAttackByBlack(bool isUnderAttackByBlack);
        void            setColor(int color);
        void            setPoint(int point);
        
        //UTILS
        inline void clearPiecesAttacks() { this->piecesAttacks.clear();};
        inline void clearPossibleMove() { this->possibleMoves.clear();};
        void upgradePawn();
        bool isTherePiece(int x, int y) const;
        std::string intToString(int x, int y) const;

    private:
        char    type;                           //type of a piece
        int     x;                              //coordinates of a piece
        int     y;                              //coordinates of a piece
        int     point;                          //point of a piece
        bool    isUnderAttackByWhite;           //is under attack by white
        bool    isUnderAttackByBlack;           //is under attack by black
        std::vector<std::string> possibleMoves; //possible moves for a piece
        std::vector<Piece> piecesAttacks;       //pieces that attack this piece
        int color;
};

#endif // PIECE_HPP