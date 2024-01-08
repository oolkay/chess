#include "../lib/Piece.hpp"

Piece::Piece() {
    this->type = ' ';
    this->x = -1;
    this->y = -1;
    this->point = 0;
    this->color = 0;
    this->isUnderAttackByBlack = 0;
    this->isUnderAttackByWhite = 0;
    std::vector<std::string> possibleMoves;
}

Piece::Piece(char _type, int color, int x, int y, int point) {
    this->type = _type;
    this->color = color;
    this->x = x;
    this->y = y;
    this->point = point;
    this->isUnderAttackByBlack = 0;
    std::vector<std::string> possibleMoves;
    this->isUnderAttackByWhite = 0;
}

Piece::~Piece() {
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
        for (auto &p : other.piecesAttacks)
        {
            this->piecesAttacks.push_back(p);
        }
        for (auto &str : other.possibleMoves)
        {
            this->possibleMoves.push_back(str);
        }
    }
    return *this;
}

bool Piece::operator==(const Piece &other) const
{
    return (this->x == other.x && this->y == other.y && this->type == other.type \
        && this->color == other.color && this->point == other.point \
        && this->isUnderAttackByBlack == other.isUnderAttackByBlack \
        && this->isUnderAttackByWhite == other.isUnderAttackByWhite );
}

char Piece::getType() const {
    return this->type;
}

int Piece::getColor() const {
    return this->color;
}

// insert the piece to vector that attacks this piece
void Piece::insertPiecesAttack(const Piece &p)
{
    this->piecesAttacks.push_back(p);
}

// insert the possible move to vector
void Piece::insertPossibleMove(std::string move)
{
    this->possibleMoves.push_back(move);
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
    this->x = coords[0] - 'a';
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

// returns if the piece is under attack by a enemy
bool Piece::getIsUnderAttack(int color) const
{
    if (color % 2 == 0)//white
        return this->isUnderAttackByBlack;
    else if (color % 2 == 1)//black
        return this->isUnderAttackByWhite;
    return 0;
}

// sets if the piece is under attack by a enemy
void Piece::setIsUnderAttack(int attackerColor, bool isUnderAttack)
{
    if (attackerColor % 2 == 1)//black
        this->isUnderAttackByBlack = isUnderAttack;
    else if (attackerColor % 2 == 0)//white
        this->isUnderAttackByWhite = isUnderAttack;
}

// returns if there is a piece at the given coordinates
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

// convert coordinates to string form
std::string Piece::intToString(int x, int y) const
{
    std::string str;
    str += x + 'a';
    str += y + '1';
    return str;
}

// for debug purposes
std::ostream &operator<<(std::ostream &os, const Piece &piece)
{
    os << "piece type: " << piece.type << std::endl;
    os << "piece color: " << piece.color << std::endl;
    os << "piece x: " << piece.x << std::endl;
    os << "piece y: " << piece.y << std::endl;
    os << "piece point: " << piece.point << std::endl;
    os << "piece isUnderAttackByBlack: " << piece.isUnderAttackByBlack << std::endl;
    os << "piece isUnderAttackByWhite: " << piece.isUnderAttackByWhite << std::endl;
    for (unsigned int i = 0; i < piece.piecesAttacks.size(); i++)
    {
        os << "piece piecesAttacks[" << i << "]: " << piece.piecesAttacks[i] << std::endl;
    }
    if (piece.piecesAttacks.size() == 0)
        os << "\npiece piecesAttacks: " << "empty";
    std::cout << "\n\n";
    return os;
}
