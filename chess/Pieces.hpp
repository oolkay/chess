#ifndef PIECES_HPP
# define PIECES_HPP

#define WPAWN 'p'
#define WKNIGHT 'n'
#define WBISHOP 'b'
#define WROOK 'r'
#define WQUEEN 'q'
#define WKING 'k'

#define BPAWN 'P'
#define BKNIGHT 'N'
#define BBISHOP 'B'
#define BROOK 'R'
#define BQUEEN 'Q'
#define BKING 'K'


#include <iostream>

class Pieces
{
    public:
        Pieces();
        Pieces(char pieceType, int indx, int letter, int point);
        Pieces(const Pieces& rhs);
        Pieces& operator=(const Pieces& rhs);
        ~Pieces();
        int move(char pieceType, int indx, int letter);
        int getIndx() const;
        int getLetter() const;
        int getPoint() const;
        char getPieceType() const;
        void setPoint(int point);
        void setPieceType(char pieceType);
        void setIndx(int indx);
        void setLetter(int letter);
        void movePawn(const std::string& destCoord);
    private:
        char    _pieceType;
        int     _indx;
        int     _letter;
        int     _point;
        int     _isUnderAttack;
        char    _color;
        
};

#endif