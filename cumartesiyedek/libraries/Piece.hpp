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
        int             getPoint() const;
        int             getColor() const;

        //SETTER
        void            setIsUnderAttack(int color, bool isUnderAttack);
        void            setAndInsert(const Piece& attackerPiece, int color);
        void            insertPiecesAttack(const Piece& p);
        void            setType(char type);
        void            setCoords(int x, int y);
        void            setCoords(std::string coords);
        void            setIsUnderAttackByWhite(bool isUnderAttackByWhite);
        void            setIsUnderAttackByBlack(bool isUnderAttackByBlack);
        void            setColor(int color);
        void            setPoint(int point);
        
        //UTILS
        inline void clearPiecesAttacks() { this->piecesAttacks.clear();};
        void upgradePawn();

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