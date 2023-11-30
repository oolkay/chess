#include "../libraries/Piece.hpp"

Piece::Piece() {
    this->type = ' ';
    this->x = -1;
    this->y = -1;
    this->point = 0;
    this->color = 0;
    this->isUnderAttack = 0;
}

Piece::Piece(char _type, int color, int x, int y, int point) {
    this->type = _type;
    this->color = color;
    this->x = x;
    this->y = y;
    this->point = point;
    this->isUnderAttack = 0;
}

Piece::~Piece() {
    // Nothing to do here
}

Piece::Piece(const Piece& other) {
    *this = other;
}

Piece& Piece::operator=(const Piece& other) {
    if (this != &other) {
        this->type = other.type;
        this->color = other.color;
        this->x = other.x;
        this->y = other.y;
        this->point = other.point;
        this->isUnderAttack = other.isUnderAttack;
    }
    return *this;
}

bool Piece::operator==(const Piece &other) const
{
    return (this->x == other.x && this->y == other.y);
}

char Piece::getType() const {
    return this->type;
}

int Piece::getColor() const {
    return this->color;
}

int Piece::getX() const{
    return this->x;
}

int Piece::getY() const{
    return this->y;
}

int Piece::getPoint() const{
    return this->point;
}

void Piece::setType(char type) {
    this->type = type;
}

void Piece::setCoords(int x, int y) {
    this->x = x;
    this->y = y;
}

void Piece::setCoords(std::string coords) {
    this->x = coords[0] - 'A';
    this->y = coords[1] - '1';
}

void Piece::setIsUnderAttack(bool isUnderAttack)
{
    this->isUnderAttack = isUnderAttack;
}
void Piece::setColor(int color)
{
    this->color = color;
}

void Piece::setPoint(int point)
{
    this->point = point;
}

std::ostream &operator<<(std::ostream &os, const Piece &piece)
{
    os << "piece type: " << piece.type << std::endl;
    os << "piece color: " << piece.color << std::endl;
    os << "piece x: " << piece.x << std::endl;
    os << "piece y: " << piece.y << std::endl;
    os << "piece point: " << piece.point << std::endl;
    os << "piece isUnderAttack: " << piece.isUnderAttack;
    return os;
}
