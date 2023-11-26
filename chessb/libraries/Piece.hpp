#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include <string>

class Piece {
    public:
        Piece();
        Piece(char _type, bool color, int x, int y, int point); // x is letters and y is numbers (A1, B2, etc.)
        ~Piece();
        Piece(const Piece& other);
        Piece& operator=(const Piece& other);
        char getType() const;
        int getX() const;
        int getY() const;
        int getPoint() const;
        bool getColor() const;
        void setType(char type);
        void setCoords(int x, int y);
        void setCoords(std::string coords);
    private:
        char type;
        int x;
        int y;
        int point;
        bool color; // 0 for black, 1 for white
};

#endif // PIECE_HPP