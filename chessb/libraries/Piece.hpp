#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include <string>

class Piece {
    public:
        Piece();
        Piece(char _type, int color, int x, int y, int point); // x is letters and y is numbers (A1, B2, etc.)
        ~Piece();
        Piece(const Piece& other);
        Piece& operator=(const Piece& other);
        bool operator==(const Piece& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
        char getType() const;
        int getX() const;
        int getY() const;
        int getPoint() const;
        int getColor() const;
        void insertPiecesAttack(const Piece& p);
        void setType(char type);
        void setCoords(int x, int y);
        void setCoords(std::string coords);
        void setIsUnderAttackByWhite(bool isUnderAttackByWhite);
        void setIsUnderAttackByBlack(bool isUnderAttackByBlack);
        void setColor(int color);
        void setPoint(int point);
        inline bool getIsUnderAttackByWhite() const { return this->isUnderAttackByWhite;};
        inline bool getIsUnderAttackByBlack() const { return this->isUnderAttackByBlack;};
        inline Piece getPieceAttacks(int i) const { return this->piecesAttacks[i];};
        inline int getPieceAttacksSize() const { return this->piecesAttacks.size();};
        inline void clearPiecesAttacks() { this->piecesAttacks.clear();};
    private:
        char type;
        int x;
        int y;
        int point;
        bool isUnderAttackByWhite;
        bool isUnderAttackByBlack;
        std::vector<std::string> possibleMoves;
        std::vector<Piece> piecesAttacks;
        int color; // 0 for black, 1 for white, -1 for empty
};

#endif // PIECE_HPP