#include "Pieces.hpp"

Pieces::Pieces(): _pieceType(0), _indx(0), _letter(0), _point(0)
{}

Pieces::Pieces(char pieceType, int indx, int letter, int point): _pieceType(pieceType), _indx(indx), _letter(letter), _point(point)
{
}

Pieces::Pieces(const Pieces &rhs)
{
    *this = rhs;
}

Pieces &Pieces::operator=(const Pieces &rhs)
{
    if (this != &rhs)
    {
        this->_pieceType = rhs._pieceType;
        this->_indx = rhs._indx;
        this->_letter = rhs._letter;
        this->_point = rhs._point;
    }
    return *this;
}

Pieces::~Pieces()
{
}

int Pieces::move(char pieceType, int indx, int letter)
{
    _indx = indx;
    _letter = letter;
    return (1);
}

int Pieces::getIndx() const
{
    return _indx;
}

int Pieces::getLetter() const
{
    return _letter;
}

int Pieces::getPoint() const
{
    return _point;
}

char Pieces::getPieceType() const
{
    return _pieceType;
}

void Pieces::setPoint(int point)
{
    _point = point;
}

void Pieces::setPieceType(char pieceType)
{
    _pieceType = pieceType;
}

void Pieces::setIndx(int indx)
{
    _indx = indx;
}

void Pieces::setLetter(int letter)
{
    _letter = letter;
}



