#include "../libraries/Piece.hpp"

Piece::Piece() {
    this->type = ' ';
    this->x = -1;
    this->y = -1;
    this->point = 0;
    this->color = 0;
    this->isUnderAttackByBlack = 0;
    this->isUnderAttackByWhite = 0;
}

Piece::Piece(char _type, int color, int x, int y, int point) {
    this->type = _type;
    this->color = color;
    this->x = x;
    this->y = y;
    this->point = point;
    this->isUnderAttackByBlack = 0;
    this->isUnderAttackByWhite = 0;
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
        this->isUnderAttackByBlack = other.isUnderAttackByBlack;
        this->isUnderAttackByWhite = other.isUnderAttackByWhite;
        this->piecesAttacks = other.piecesAttacks;
    }
    return *this;
}

bool Piece::operator==(const Piece &other) const
{
    return (this->x == other.x && this->y == other.y && this->type == other.type \
        && this->color == other.color && this->point == other.point \
        && this->isUnderAttackByBlack == other.isUnderAttackByBlack \
        && this->isUnderAttackByWhite == other.isUnderAttackByWhite \
        && this->piecesAttacks == other.piecesAttacks \
        && this->possibleMoves == other.possibleMoves);
}

char Piece::getType() const {
    return this->type;
}

int Piece::getColor() const {
    return this->color;
}

void Piece::insertPiecesAttack(const Piece& p)
{
    this->piecesAttacks.push_back(p);
}

int Piece::getX() const
{
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

void Piece::setIsUnderAttackByWhite(bool isUnderAttackByWhite)
{
    this->isUnderAttackByWhite = isUnderAttackByWhite;
}

void Piece::setIsUnderAttackByBlack(bool isUnderAttack)
{
    this->isUnderAttackByBlack = isUnderAttack;
}
void Piece::setColor(int color)
{
    this->color = color;
}

void Piece::setPoint(int point)
{
    this->point = point;
}

bool Piece::getIsUnderAttack(int color) const
{
    if (color == 0)//white
        return this->isUnderAttackByBlack;
    else
        return this->isUnderAttackByWhite;
}
void Piece::setIsUnderAttack(int color, bool isUnderAttack)
{
    if (color == 1)//black
        this->isUnderAttackByBlack = isUnderAttack;
    else
        this->isUnderAttackByWhite = isUnderAttack;
}

void Piece::setAndInsert(const Piece& attackerPiece, int color)
{
    setIsUnderAttack(color, 1);
    this->piecesAttacks.push_back(attackerPiece);
}

void Piece::upgradePawn()
{
    std::string type;
    std::cout << "Choose a piece to upgrade your pawn: ";
    getline(std::cin, type);
    if (this->color == 0)
    {
        if (type[0] == 'R' || type[0] == 'B' || type[0] == 'N' || type[0] == 'Q')
        {
            this->type = type[0];
            if (type[0] == 'R' || type[0] == 'r') point = 5;
            else if (type[0] == 'B' || type[0] == 'b') point = 3;
            else if (type[0] == 'N' || type[0] == 'n') point = 3;
            else if (type[0] == 'Q' || type[0] == 'q') point = 9;
        }
        else
        {
            std::cout << "Invalid piece, your pawn will be upgraded to Queen\n";
            this->type = 'Q';
            point = 9;
        }
    }
    else if (color == 1)
    {
        if (type[0] == 'r' || type[0] == 'b' || type[0] == 'n' || type[0] == 'q')
        {
            this->type = type[0];
            if (type[0] == 'r' || type[0] == 'R') point = 5;
            else if (type[0] == 'b' || type[0] == 'B') point = 3;
            else if (type[0] == 'n' || type[0] == 'N') point = 3;
            else if (type[0] == 'q' || type[0] == 'Q') point = 9;
        }
        else
        {
            std::cout << "Invalid piece, your pawn will be upgraded to Queen\n";
            this->type = 'q';
            point = 9;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Piece &piece)
{
    os << "piece type: " << piece.type << std::endl;
    os << "piece color: " << piece.color << std::endl;
    os << "piece x: " << piece.x << std::endl;
    os << "piece y: " << piece.y << std::endl;
    os << "piece point: " << piece.point << std::endl;
    os << "piece isUnderAttackByBlack: " << piece.isUnderAttackByBlack;
    os << "piece isUnderAttackByWhite: " << piece.isUnderAttackByWhite;
    for (int i = 0; i < piece.piecesAttacks.size(); i++)
    {

        os << "piece piecesAttacks[" << i << "]: " << piece.piecesAttacks[i];
    }
    if (piece.piecesAttacks.size() == 0)
        os << "\npiece piecesAttacks: " << "empty";
    return os;
}
