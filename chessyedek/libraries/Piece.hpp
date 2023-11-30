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
        void setType(char type);
        void setCoords(int x, int y);
        void setCoords(std::string coords);
        void setIsUnderAttack(bool isUnderAttack);
        void setColor(int color);
        void setPoint(int point);
        inline bool getIsUnderAttack() const { return this->isUnderAttack;};
    private:
        char type;
        int x;
        int y;
        int point;
        bool isUnderAttack;
        int color; // 0 for black, 1 for white, -1 for empty
};

#endif // PIECE_HPP