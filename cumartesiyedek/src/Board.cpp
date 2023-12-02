#include "../libraries/Board.hpp"
#include <math.h>

int Board::turn = 0;//white starts first

Board::Board() {
    std::vector< std::vector<Piece> > board(8, std::vector<Piece>(8));
    std::vector<Piece> whiteP;
    std::vector<Piece> blackP;
    whiteP.push_back(Piece('R', 0, 0, 0, 5));
    whiteP.push_back(Piece('N', 0, 1, 0, 3));
    whiteP.push_back(Piece('B', 0, 2, 0, 3));
    whiteP.push_back(Piece('Q', 0, 3, 0, 9));
    whiteP.push_back(Piece('K', 0, 4, 0, 0));
    whiteP.push_back(Piece('B', 0, 5, 0, 3));
    whiteP.push_back(Piece('N', 0, 6, 0, 3));
    whiteP.push_back(Piece('R', 0, 7, 0, 5));
    for (int i = 0; i < 8; i++) {
        whiteP.push_back(Piece('P', 0, i, 1, 1));
    }

    blackP.push_back(Piece('r', 1, 0, 7, 5));
    blackP.push_back(Piece('n', 1, 1, 7, 3));
    blackP.push_back(Piece('b', 1, 2, 7, 3));
    blackP.push_back(Piece('q', 1, 3, 7, 9));
    blackP.push_back(Piece('k', 1, 4, 7, 0));
    blackP.push_back(Piece('b', 1, 5, 7, 3));
    blackP.push_back(Piece('n', 1, 6, 7, 3));
    blackP.push_back(Piece('r', 1, 7, 7, 5));
    for (int i = 0; i < 8; i++) {
        blackP.push_back(Piece('p', 1, i, 6, 1));
    }

    for (Piece p : whiteP) {
        board[p.getY()][p.getX()] = p;
    }
    for (Piece p : blackP) {
        board[p.getY()][p.getX()] = p;
    }
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = Piece('.', -1, j, i, 0);
        }
    }
    this->board = board;
}

Board::~Board() {
    // std::cout << "Board destructor called" << std::endl;
}

Board::Board(const Board& other) {
    this->board = other.board;
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        this->board = other.board;
    }
    return *this;
}

//only checks the format of the input, not the validity of the move
bool Board::checkInputFormat(const std::string &input) const
{
    if (input.length() != 4 || input.empty())
    {
        std::cout << "\n[Invalid Format, example format: e3e4]\n";
        return false;
    }
    std::string piece = input.substr(0,2); // e2
    std::string dest = input.substr(2,4); // e4
    if (piece[0] < 'a' || piece[0] > 'h' || dest[0] < 'a' || dest[0] > 'h')
    {
        std::cout << "\n[Invalid File, please enter file between a-h]\n";
        return false;
    }
    if (piece[1] < '1' || piece[1] > '8')
    {
        std::cout << "\n[Invalid Rank, please enter rank between 1-8]\n";
        return false;
    }
    return true;
}

//checks the validity of the move for ex: e2e4
bool Board::validateMove(const std::string &input)
{
    std::string piece = input.substr(0,2); // e2
    std::string dest = input.substr(2,4); // e4
    int oldX = piece[0] - 'a';
    int oldY = piece[1] - '1';
    int newX = dest[0] - 'a';
    int newY = dest[1] - '1';
    const Piece& p = board[oldY][oldX];
    char pieceType = p.getType();

    // check if the piece is in the board
    if (isTherePiece(oldX, oldY) == false)
    {
        std::cout << "\n[There is no piece in the given coordinates]\n";
        return false;
    }
    // trying to eat same color
    if (isTherePiece(newX, newY) == true)
    {
        if (board[newY][newX].getColor() == p.getColor())
        {
            std::cout << "\n[You can not eat your own piece]\n";
            return false;
        }
    }
    // if white's turn, check if the piece is white
    //todo: error msga1
    if (turn % 2 == 0)
    {
        if (p.getColor() == 1)
        {
            std::cout << "\n[It is white's turn]\n";
            return false;
        }
    }
    // if black's turn, check if the piece is 
    else
    {
        if (p.getColor() == 0)
        {
            std::cout << "\n[It is black's turn]\n";
            return false;
        }
    }

    /*CHECK WHICH PIECE*/
    if (pieceType == 'P' || pieceType == 'p')
    {
        if (validatePawnMove(oldX, oldY, newX, newY) == false) {
            std::cout << "\n[The pawn can not move to the given cell]\n";
            return false;
        }
    }
    else if (pieceType == 'R' || pieceType == 'r')
    {
        if (validateRookMove(oldX, oldY, newX, newY) == false) {
            std::cout << "\n[The rook can not move to the given cell]\n"; 
            return false;
        }
    }
    else if (pieceType == 'B' || pieceType == 'b')
    {
        if (validateBishopMove(oldX, oldY, newX, newY) == false) {
            std::cout << "\n[The bishop can not move to the given cell]\n";
            return false;
        }
    }
    else if (pieceType == 'N' || pieceType == 'n')
    {
        if (validateKnightMove(oldX, oldY, newX, newY) == false) {
            std::cout << "\n[The knight can not move to the given cell]\n";
            return false;
        }
    }
    else if (pieceType == 'Q' || pieceType == 'q')
    {
        if (validateBishopMove(oldX, oldY, newX, newY) == false && validateRookMove(oldX, oldY, newX, newY) == false) {
            std::cout << "\n[The queen can not move to the given cell]\n";
            return false;
        }
    }
    else if (pieceType == 'K' || pieceType == 'k')
    {
        if (validateKingMove(oldX, oldY, newX, newY) == false) {
            std::cout << "\n[The king can not move to the given cell]\n";
            return false;
        }
    }
    return true;
}

bool Board::validatePawnMove(int oldX, int oldY, int newX, int newY) const
{
    const Piece& destCell = board[newY][newX];
    const Piece& currentPiece = board[oldY][oldX];
    const char type = destCell.getType();

    if (currentPiece.getColor() == 0)
    {    
        if (oldX == newX && newY == oldY + 1 && type == '.') {
            return true;
        }
        else if (oldX == newX && newY == oldY + 2 && oldY == 1 && type == '.') {
            if (board[oldY + 1][oldX].getType() == '.')
                return true;
        }
        else if (newY == oldY + 1 && newX == oldX + 1 && type != '.') {
            return true;
        }
        else if (newY == oldY + 1 && newX == oldX - 1 && type != '.') {
            return true;
        }
    }
    else
    {
        if (oldX == newX && newY == oldY - 1 && type == '.') {
            return true;
        }
        else if (oldX == newX && newY == oldY - 2 && oldY == 6 && type == '.') {
            if (board[oldY - 1][oldX].getType() == '.')
                return true;
        }
        else if (newY == oldY - 1 && newX == oldX + 1 && type != '.') {
            return true;
        }
        else if (newY == oldY - 1 && newX == oldX - 1 && type != '.') {
            return true;
        }
    }
    return false;
}

bool Board::validateRookMove(int oldX, int oldY, int newX, int newY) const
{
    const Piece& destCell = board[newY][newX];
    //moves vertically
    if (oldX == newX)
    {
        //moves up
        if (oldY < newY) {
            for (int i = oldY + 1; i < newY; i++)
                if (board[i][oldX].getType() != '.')
                    return false;
        }
        //moves down
        else
        {
            for (int i = oldY - 1; i > newY; i--)
                if (board[i][oldX].getType() != '.')
                    return false;
        }
        return true;
    }
    //moves horizontally
    else if (oldY == newY)
    {
        //moves right
        if (oldX < newX) {
            for (int i = oldX + 1; i < newX; i++)
                if (board[oldY][i].getType() != '.')
                    return false;
        }
        //moves left
        else
        {
            for (int i = oldX - 1; i > newX; i--)
                if (board[oldY][i].getType() != '.')
                    return false;
        }
        return true;
    }
    return false;
}

bool Board::validateBishopMove(int oldX, int oldY, int newX, int newY) const
{
    const Piece& destCell = board[newY][newX];
    int i = 0;
    int j = 0;
    //moves diagonally
    if (oldX != newX && oldY != newY)
    {
        //moves up right
        if (oldX < newX && oldY < newY)
        {
            for (i = oldX + 1, j = oldY + 1; i < newX && j < newY; i++, j++)
            {
                if (board[j][i].getType() != '.' && i < newX && j < newY)
                    return false;
            }
        }
        //moves up left
        else if (oldX > newX && oldY < newY)
        {
            for (i = oldX - 1, j = oldY + 1; i > newX && j < newY; i--, j++)
            {
                if (board[j][i].getType() != '.' && i <= newX && j <= newY)
                    return false;
            }
        }
        //moves down right
        else if (oldX < newX && oldY > newY)
        {
            for (i = oldX + 1, j = oldY - 1; i < newX && j > newY; i++, j--)
            {
                if (board[j][i].getType() != '.' && i <= newX && j <= newY)
                    return false;
            }
        }
        //moves down left
        else if (oldX > newX && oldY > newY)
        {
            for (i = oldX - 1, j = oldY - 1; i > newX && j > newY; i--, j--)
            {
                if (board[j][i].getType() != '.' && i < newX && j < newY)
                    return false;
            }
        }
        if (j != newY || i != newX)
            return false;
        // if (destCell.getType() != '.')
        // {
        //     if (destCell.getColor() == 0 && turn % 2 == 0)
        //         return false;
        //     else if (destCell.getColor() == 1 && turn % 2 == 1)
        //         return false;
        // }
        return true;
    }
    return false;
}

bool Board::validateKnightMove(int oldX, int oldY, int newX, int newY) const
{
    if ((abs(oldX-newX) == 2 && abs(oldY-newY) == 1) || (abs(oldX-newX) == 1 && abs(oldY-newY) == 2))
        return true;
    return false;
}

bool Board::validateKingMove(int oldX, int oldY, int newX, int newY) const
{
    const Piece& destCell = board[newY][newX];
    const int pieceColor = board[oldY][oldX].getColor();
    bool isUnderAttack;
    if (pieceColor == WHITE)
        isUnderAttack = destCell.getIsUnderAttackByBlack();
    else if (pieceColor == BLACK)
        isUnderAttack = destCell.getIsUnderAttackByWhite();
    if (newX == oldX + 1 && newY == oldY && isUnderAttack == false) return true;
    else if (newX == oldX + 1 && newY == oldY + 1 && isUnderAttack == false) return true;
    else if (newX == oldX && newY == oldY + 1 && isUnderAttack == false) return true;
    else if (newX == oldX - 1 && newY == oldY + 1 && isUnderAttack == false) return true;
    else if (newX == oldX - 1 && newY == oldY && isUnderAttack == false) return true;
    else if (newX == oldX - 1 && newY == oldY - 1 && isUnderAttack == false) return true;
    else if (newX == oldX && newY == oldY - 1 && isUnderAttack == false) return true;
    else if (newX == oldX + 1 && newY == oldY - 1 && isUnderAttack == false) return true;
    std::cout << "\n[The king can not move to the given cell, it is check you need to protect your king!]\n";
    return false;
}

bool Board::isCheckmate(int color)
{
    if (isCheck(color) == 0)
        return false;
    Piece& king = getKing(color);
    int x = king.getX();
    int y = king.getY();
    int flag = 1;
    if (king.getIsUnderAttack(color) == false)
        return false;

    //CAN KING MOVE
    if (x+1 < 8 && board[y][x+1].getIsUnderAttack(color) == false && board[y][x+1].getColor() != color) return false;
    if (x+1 < 8 && y+1 < 8 && board[y+1][x+1].getIsUnderAttack(color) == false && board[y+1][x+1].getColor() != color) return false;
    if (y+1 < 8 && board[y+1][x].getIsUnderAttack(color) == false && board[y+1][x].getColor() != color) return false;
    if (x-1 >= 0 && y+1 < 8 && board[y+1][x-1].getIsUnderAttack(color) == false && board[y+1][x-1].getColor() != color) return false;
    if (x-1 >= 0 && board[y][x-1].getIsUnderAttack(color) == false && board[y][x-1].getColor() != color) return false;
    if (x-1 >= 0 && y-1 >= 0 && board[y-1][x-1].getIsUnderAttack(color) == false && board[y-1][x-1].getColor() != color) return false;
    if (y-1 >= 0 && board[y-1][x].getIsUnderAttack(color) == false && board[y-1][x].getColor() != color) return false;
    if (x+1 < 8 && y-1 >= 0 && board[y-1][x+1].getIsUnderAttack(color) == false && board[y-1][x+1].getColor() != color) return false;

    //THIS IS THE CASE, WHERE THE KING IS UNDER ATTACK BY TWO OR MORE PIECES AND KING CAN NOT MOVE
    int size = king.getPieceAttacksSize();
    if (size > 1)
        return true;

    //CAN ANY PIECE PROTECET THE KING BY EATING THE ATTACKING PIECE
    const Piece& attackPiece = king.getPieceAttacks(0);
    Piece tmp = attackPiece;
    const std::vector<Piece>& piecesDefends = attackPiece.getAttackers();

    const int attackColor = attackPiece.getColor();
    const int defenderSize = attackPiece.getPieceAttacksSize();

    for (const auto defenderPiece : piecesDefends)
    {
        movePiece(defenderPiece.getX(), defenderPiece.getY(), attackPiece.getX(), attackPiece.getY());
        updateUnderAttack();
        if (isCheck(color) == false)
        {
            undoMove(tmp, attackPiece.getX(), attackPiece.getY(), defenderPiece.getX(), defenderPiece.getY());
            return false;
        }
    }

    std::cout << "debug\n";
    //CAN ANY PIECE PROTECT THE KING BY BLOCKING THE ATTACKING PIECE
    flag = 1;

    const char type = attackPiece.getType();
    if (type == 'R' || type == 'r') {
        if (saveTheKingFromRook(king, attackPiece) == true)
            return false;
    }
    else if (type == 'B' || type == 'b') {
        if (saveTheKingFromBishop(king, attackPiece) == true)
            return false;
    }
    else if (type == 'Q' || type == 'q')
    {
        if (attackPiece.getX() == king.getX() || attackPiece.getY() == king.getY())
            if (saveTheKingFromRook(king, attackPiece) == true)
                return false;
        else
            if (saveTheKingFromBishop(king, attackPiece) == true)
                return false;
    }
    return true;
}

bool Board::isWhiteCheck()
{
    Piece& king = getKing(0);
    if (king.getIsUnderAttackByBlack() == true)
        return true;
    return false;
}

bool Board::isCheck(int color)
{
    const Piece& king = getKing(color);
    if (color == 0) {
        if (king.getIsUnderAttackByBlack() == true)
            return true;
        return false;
    }
    else {
        if (king.getIsUnderAttackByWhite() == true)
            return true;
        return false;
    }
}

bool Board::isBlackCheck()
{
    Piece& king = getKing(0);
    if (king.getIsUnderAttackByBlack() == true)
        return true;
    return false;
}

Piece &Board::getKing(int color)
{
    char pieceType;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8 ; j++)
        {
            pieceType = board[i][j].getType();
            if ((pieceType == 'K' || pieceType == 'k') && board[i][j].getColor() == color)
                return board[i][j];
        }
    }
    std::cout << "The King is not present on the board\n";
    exit(-1);
}

bool Board::checkAllDefenders(const Piece& p)
{
    int size = p.getPieceAttacksSize();
    int color = getTurn() % 2;
    for (int indx = 0; indx < size; ++indx)
    {
        const Piece& defenderPiece = p.getPieceAttacks(indx);
        char type = p.getPieceAttacks(indx).getType();
        Piece tmp = p;
        if ((type == 'R' || type == 'Q' || type == 'N' || type == 'B' || 
                type == 'r' || type == 'q' || type == 'n' || type == 'b') && defenderPiece.getColor() == color)
        {
            movePiece(defenderPiece.getX(), defenderPiece.getY(), p.getX(), p.getY());
            updateUnderAttack();
            if (isCheck(color) == false)
            {
                std::cout << *this << std::endl;
                undoMove(tmp, p.getX(), p.getY(), defenderPiece.getX(), defenderPiece.getY());
                return true;
            }
            else
                undoMove(tmp, p.getX(), p.getY(), defenderPiece.getX(), defenderPiece.getY());
        }
    }
    return false;
}

bool Board::isTherePiece(int x, int y) const
{
    if (board[y][x].getType() != '.')
        return true;
    else
        return false;
    return false;
}

int Board::movePiece(int oldX, int oldY, int newX, int newY)
{
    Piece& oldCell = board[oldY][oldX];
    Piece& newCell = board[newY][newX];
    Piece tmp = board[newY][newX];
    if (oldCell.getType() == 'P' || oldCell.getType() == 'p')
    {
        if (oldCell.getColor() == WHITE && newY == 7)
            oldCell.upgradePawn();
        else if (oldCell.getColor() == BLACK && newY == 0)
            oldCell.upgradePawn();
    }
    newCell.setType(oldCell.getType());
    newCell.setColor(oldCell.getColor());
    newCell.setPoint(oldCell.getPoint());
    oldCell.setType('.');
    oldCell.setColor(-1);
    oldCell.setPoint(0);
    updateUnderAttack();
    if (isCheck(turn % 2) == true) {
        undoMove(tmp, newX, newY, oldX, oldY);
        std::cout << "\n[It is check, you need to protect your king!]\n";
        return 0;
    }
    return (1);
}

void Board::undoMove(const Piece& oldPiece, int oldX, int oldY, int newX, int newY)
{
    Piece& newCell = board[newY][newX];
    Piece& oldCell = board[oldY][oldX];
    newCell.setType(oldCell.getType());
    newCell.setColor(oldCell.getColor());
    newCell.setPoint(oldCell.getPoint());
    oldCell.setType(oldPiece.getType());
    oldCell.setColor(oldPiece.getColor());
    oldCell.setPoint(oldPiece.getPoint());
    updateUnderAttack();
}

void Board::setTurn(int turn)
{
    Board::turn = turn;
}

void Board::isPawnAttacks(const Piece &p)
{
    int x = p.getX();
    int y = p.getY();
    if (p.getColor() == 0) {
        if (x + 1 < 8 && y + 1 < 8) {
            if (board[y + 1][x + 1].getColor() != 0)
                board[y + 1][x + 1].setAndInsert(p, WHITE);
        }
        if (x - 1 >= 0 && y + 1 < 8) {
            if (board[y + 1][x - 1].getColor() != 0)
                board[y + 1][x - 1].setAndInsert(p, WHITE);
        }
    }
    else if (p.getColor() == 1) {
        if (x + 1 < 8 && y - 1 >= 0) {
            if (board[y - 1][x + 1].getColor() != 1)
                board[y - 1][x + 1].setAndInsert(p, BLACK);
        }
        if (x - 1 >= 0 && y - 1 >= 0) {
            if (board[y - 1][x - 1].getColor() != 1)
                board[y - 1][x - 1].setAndInsert(p, BLACK);
        }
    }
}

void Board::isRookAttacks(const Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    int i = pieceY + 1;
    //checks up
    for (int i = pieceY + 1; i < 8 && board[i][pieceX].getColor() != pieceColor; i++) {
        board[i][pieceX].setAndInsert(p, pieceColor);
        if (board[i][pieceX].getType() != '.')
            break;
    }
    //checks down
    for (int i = pieceY - 1; i >= 0 && board[i][pieceX].getColor() != pieceColor; i--) {
        board[i][pieceX].setAndInsert(p, pieceColor);
        if (board[i][pieceX].getType() != '.')
            break;
    }
    //checks right
    for (int i = pieceX + 1; i < 8 && board[pieceY][i].getColor() != pieceColor; i++) {
        board[pieceY][i].setAndInsert(p, pieceColor);
        if (board[pieceY][i].getType() != '.')
            break;
    }
    //checks left
    for (int i = pieceX - 1; i >= 0 && board[pieceY][i].getColor() != pieceColor; i--) {
        board[pieceY][i].setAndInsert(p, pieceColor);
        if (board[pieceY][i].getType() != '.')
            break;
    }
}

void Board::isBishopAttacks(const Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    //checks up-right
    for (int i = pieceX + 1, j = pieceY + 1; i < 8 && j < 8 ; i++, j++)
    {
        board[j][i].setAndInsert(p, pieceColor);
        if (board[j][i].getType() != '.')
            break;
    }
    //checks up-left
    for (int i = pieceX - 1, j = pieceY + 1; i >= 0 && j < 8 && board[j][i].getColor() != pieceColor; i--, j++)
    {
        board[j][i].setAndInsert(p, pieceColor);
        if (board[j][i].getType() != '.')
            break;
    }
    //checks down-right
    for (int i = pieceX + 1, j = pieceY - 1; i < 8 && j >= 0 && board[j][i].getColor() != pieceColor; i++, j--)
    {
        board[j][i].setAndInsert(p, pieceColor);
        if (board[j][i].getType() != '.')
            break;
    }
    //checks down-left
    for (int i = pieceX - 1, j = pieceY - 1; i >= 0 && j >= 0 && board[j][i].getColor() != pieceColor; i--, j--)
    {
        board[j][i].setAndInsert(p, pieceColor);
        if (board[j][i].getType() != '.')
            break;
    }
}

void Board::isKnightAttacks(const Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    //   ___
    //  |
    //  |    
    if (pieceX + 1 < 8 && pieceY + 2 < 8) {
        if (board[pieceY + 2][pieceX + 1].getColor() != pieceColor)
            board[pieceY+2][pieceX+1].setAndInsert(p, pieceColor);
    }
    //   ____
    //  |
    if (pieceX + 2 < 8 && pieceY + 1 < 8) {
        if (board[pieceY + 1][pieceX + 2].getColor() != pieceColor)
            board[pieceY + 1][pieceX + 2].setAndInsert(p, pieceColor);
    }
    //   ____
    //      |
    if (pieceX + 2 < 8 && pieceY - 1 >= 0) {
        if (board[pieceY - 1][pieceX + 2].getColor() != pieceColor)
            board[pieceY - 1][pieceX + 2].setAndInsert(p, pieceColor);
    }
    //   ___
    //      |
    //      |
    if (pieceX + 1 < 8 && pieceY - 2 >= 0) {
        if (board[pieceY - 2][pieceX + 1].getColor() != pieceColor)
            board[pieceY - 2][pieceX + 1].setAndInsert(p, pieceColor);
    }
    //      ___
    //      |
    //      |
    if (pieceX - 1 >= 0 && pieceY - 2 >= 0) {
        if (board[pieceY - 2][pieceX - 1].getColor() != pieceColor)
            board[pieceY - 2][pieceX - 1].setAndInsert(p, pieceColor);
    }
    //      ____
    //      |
    if (pieceX - 2 >= 0 && pieceY - 1 >= 0) {
        if (board[pieceY - 1][pieceX - 2].getColor() != pieceColor)
            board[pieceY - 1][pieceX - 2].setAndInsert(p, pieceColor);
    }
    //     |____
    if (pieceX - 2 >= 0 && pieceY + 1 < 8) {
        if (board[pieceY + 1][pieceX - 2].getColor() != pieceColor)
            board[pieceY + 1][pieceX - 2].setAndInsert(p, pieceColor);
    }
    //  |
    //  |
    //  |____
    if (pieceX - 1 >= 0 && pieceY + 2 < 8) {
        if (board[pieceY + 2][pieceX - 1].getColor() != pieceColor)
            board[pieceY + 2][pieceX - 1].setAndInsert(p, pieceColor);
    }
}

void Board::isQueenAttacks(const Piece &p)
{
    isBishopAttacks(p);
    isRookAttacks(p);
}

void Board::isKingAttacks(const Piece &p)
{
    int x = p.getX();
    int y = p.getY();
    const int pieceColor = p.getColor();
    //check up-left, up, up-right
    if (y + 1 < 8) {
        if (x - 1 >= 0) {
            if (board[y + 1][x - 1].getColor() != pieceColor)
                if (board[y + 1][x - 1].getIsUnderAttack(pieceColor+1) == false)
                    board[y + 1][x - 1].setAndInsert(p, pieceColor);
        }
        if (board[y + 1][x].getColor() != pieceColor)
            if (board[y + 1][x].getIsUnderAttack(pieceColor+1) == false)
                board[y + 1][x].setAndInsert(p, pieceColor);
        if (x + 1 < 8) {
            if (board[y + 1][x + 1].getColor() != pieceColor)
                if (board[y + 1][x + 1].getIsUnderAttack(pieceColor+1) == false)
                    board[y + 1][x + 1].setAndInsert(p, pieceColor);
        }
    }
    //check left, right
    if (x - 1 >= 0) {
        if (board[y][x - 1].getColor() != pieceColor)
            if (board[y][x - 1].getIsUnderAttack(pieceColor+1) == false)
                board[y][x - 1].setAndInsert(p, pieceColor);
    }
    if (x + 1 < 8) {
        if (board[y][x + 1].getColor() != pieceColor)
            if (board[y][x + 1].getIsUnderAttack(pieceColor+1) == false)
                board[y][x + 1].setAndInsert(p, pieceColor);
    }
    //check down-left, down, down-right
    if (y - 1 >= 0) {
        if (x - 1 >= 0) {
            if (board[y - 1][x - 1].getColor() != pieceColor)
                if (board[y - 1][x - 1].getIsUnderAttack(pieceColor+1) == false)
                    board[y - 1][x - 1].setAndInsert(p, pieceColor);
        }
        if (board[y - 1][x].getColor() != pieceColor) {
            if (board[y - 1][x].getIsUnderAttack(pieceColor+1) == false)
                board[y - 1][x].setAndInsert(p, pieceColor);
        }
        if (x + 1 < 8) {
            if (board[y - 1][x + 1].getColor() != pieceColor)
                if (board[y - 1][x + 1].getIsUnderAttack(pieceColor+1) == false)
                    board[y - 1][x + 1].setAndInsert(p, pieceColor);
        }
    }
}

void Board::updateUnderAttack()
{
    for (int i = 0; i < 64; i++)
    {
        board[i / 8][i % 8].setIsUnderAttackByBlack(false);
        board[i / 8][i % 8].setIsUnderAttackByWhite(false);
        board[i / 8][i % 8].clearPiecesAttacks();
    }
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Piece& p = board[i][j];
            if ((p.getType() == 'P' || p.getType() == 'p'))
                isPawnAttacks(p);
            else if ((p.getType() == 'R' || p.getType() == 'r'))
                isRookAttacks(p);
            else if ((p.getType() == 'B' || p.getType() == 'b'))
                isBishopAttacks(p);
            else if ((p.getType() == 'N' || p.getType() == 'n'))
                isKnightAttacks(p);
            else if ((p.getType() == 'Q' || p.getType() == 'q'))
                isQueenAttacks(p);
            else if ((p.getType() == 'K' || p.getType() == 'k'))
                isKingAttacks(p);
        }
    }
}

void Board::score()
{
    double whiteScore = 0;
    double blackScore = 0;
    double pieceScore = 0;
    // updateUnderAttack();//this function will update the isUnderAttack of each piece
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Piece& p = board[i][j];
            pieceScore = (double)p.getPoint();
            if (p.getColor() == 0)
            {
                whiteScore += pieceScore - 0.5 * (double)p.getIsUnderAttackByBlack()*pieceScore;
            }
            else if (p.getColor() == 1)
            {
                blackScore += pieceScore - 0.5 * (double)p.getIsUnderAttackByWhite()*pieceScore;
            }
        }
    }
    std::cout << "White score: " << whiteScore << std::endl;
    std::cout << "Black score: " << blackScore << std::endl;                   
}

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    const std::vector< std::vector<Piece> > &b = board.board;
    std::cout << std::endl;
    for (int i = 7; i >= 0; --i) {
        std::cout << i + 1 << " | ";
        for (int j = 0; j < 8; j++)
            std::cout << b[i][j].getType() << " ";
        std::cout << std::endl;
    }
    std::cout << "    - - - - - - - -" << std::endl;
    std::cout << "    ";
    for (int i = 0; i < 8; i++)
        std::cout << (char)('a' + i) << " ";

    // std::cout << "\n\n\n";
    // for (int i = 7; i >= 0; --i) {
    //     std::cout << i + 1 << " | ";
    //     for (int j = 0; j < 8; j++)
    //         std::cout << b[i][j].getIsUnderAttackByWhite() << " ";
    //     std::cout << std::endl;
    // }
    // std::cout << "    - - - - - - - -" << std::endl;
    // std::cout << "    ";
    // for (int i = 0; i < 8; i++)
    //     std::cout << (char)('a' + i) << " ";

    // std::cout << "\n\n\n";
    // for (int i = 7; i >= 0; --i) {
    //     std::cout << i + 1 << " | ";
    //     for (int j = 0; j < 8; j++)
    //         std::cout << b[i][j].getIsUnderAttackByBlack() << " ";
    //     std::cout << std::endl;
    // }
    // std::cout << "    - - - - - - - -" << std::endl;
    // std::cout << "    ";
    // for (int i = 0; i < 8; i++)
    //     std::cout << (char)('a' + i) << " ";
    return os;
}

bool Board::saveTheKingFromRook(const Piece& king, const Piece& rook)
{
    int kingX = king.getX();
    int kingY = king.getY();
    int rookX = rook.getX();
    int rookY = rook.getY();
    int pieceColor = king.getColor();
    int i = 0;
    int j = 0;
    int size = 0;
    //checks up
    if (kingX == rookX && kingY < rookY) {
        for (i = kingY + 1; i < rookY; i++) {
            const Piece& p = board[i][kingX];
            if (p.getIsUnderAttack(pieceColor + 1) == true)
                if (checkAllDefenders(p))
                    return true;
        }
    }
    //checks down
    else if (kingX == rookX && kingY > rookY) {
        for (i = kingY - 1; i > rookY; i--) {
            const Piece& p = board[i][kingX];
            if (p.getIsUnderAttack(pieceColor + 1) == true)
                if (checkAllDefenders(p))
                    return true;
        }
    }
    //checks right
    else if (kingX < rookX && kingY == rookY) {

        for (i = kingX + 1; i < rookX; i++) {
            if (checkAnyPawnDefendsRook(i, king) == true)
                return true;
            const Piece& p = board[kingY][i];
            if (p.getIsUnderAttack(pieceColor + 1) == true)
                if (checkAllDefenders(p))
                    return true;
        }
    }
    //checks left
    else if (kingX > rookX && kingY == rookY){
        for (i = kingX - 1; i > rookX; i--){
            if (checkAnyPawnDefendsRook(i, king) == true)
                return true;
            const Piece& p = board[kingY][i];
            if (p.getIsUnderAttack(pieceColor + 1) == true)
                if (checkAllDefenders(p))
                    return true;
        }
    }
    return false;
}

bool Board::checkAnyPawnDefendsRook(int coordX, const Piece& king)
{
    int kingX = king.getX(), kingY = king.getY();
    int color = king.getColor();
    if (coordX < kingX)
    {
        if (color == BLACK)
        {
            if (kingY + 1 < 8)
                if (board[kingY + 1][coordX].getType() == 'p' && board[kingY + 1][coordX].getColor() == color)
                    return true;
        }
        else
        {
            if (kingY - 1 >= 0)
                if (board[kingY - 1][coordX].getType() == 'P' && board[kingY - 1][coordX].getColor() == color)
                    return true;
        }
    }
    else
    {
        if (color == BLACK)
        {
            if (kingY + 1 < 8)
                if (board[kingY + 1][coordX].getType() == 'p' && board[kingY + 1][coordX].getColor() == color)
                    return true;
        }
        else
        {
            if (kingY - 1 >= 0)
                if (board[kingY - 1][coordX].getType() == 'P' && board[kingY - 1][coordX].getColor() == color)
                    return true;
        }
    }
    return false;
}

bool Board::saveTheKingFromBishop(const Piece &king, const Piece &bishop)
{
    int kingX = king.getX();
    int kingY = king.getY();
    int bishopX = bishop.getX();
    int bishopY = bishop.getY();
    int pieceColor = king.getColor();
    int i = 0;
    int j = 0;
    int size = 0;
    //checks up-right
    if (kingX < bishopX && kingY < bishopY)
    {
        for (i = kingX + 1, j = kingY + 1; i < bishopX && j < bishopY; i++, j++) {
            if (checkAnyPawnDefendsBishop(i, j, king) == true)
                return true;
            const Piece& p = board[j][i];
            if (p.getIsUnderAttack(pieceColor+1) == true)
                if (checkAllDefenders(p))
                    return true;
        }
    }
    //checks up-left
    else if (kingX > bishopX && kingY < bishopY){
        for (i = kingX - 1, j = kingY + 1; i > bishopX && j < bishopY; i--, j++) {
            if (checkAnyPawnDefendsBishop(i, j, king) == true)
                return true;
            const Piece& p = board[j][i];
            if (p.getIsUnderAttack(pieceColor+1) == true)
                if (checkAllDefenders(p))
                    return true;
        }
    }
    //checks down-right
    else if (kingX < bishopX && kingY > bishopY){
        for (i = kingX + 1, j = kingY - 1; i < bishopX && j > bishopY; i++, j--) {
            if (checkAnyPawnDefendsBishop(i, j, king) == true)
                return true;
            const Piece& p = board[j][i];
            if (p.getIsUnderAttack(pieceColor+1) == true)
                if (checkAllDefenders(p))
                    return true;
        }
    }
    //checks down-left
    else if (kingX > bishopX && kingY > bishopY) 
        for (i = kingX - 1, j = kingY - 1; i > bishopX && j > bishopY; i--, j--) {
            if (checkAnyPawnDefendsBishop(i, j, king) == true)
                return true;
            const Piece& p = board[j][i];
            if (p.getIsUnderAttack(pieceColor+1) == true)
                if (checkAllDefenders(p))
                    return true;
    }
    return false;
}

bool Board::checkAnyPawnDefendsBishop(int coordX, int coordY, const Piece& king)
{
    int kingX = king.getX(), kingY = king.getY();
    int color = king.getColor();
    if (coordX < kingX && coordY < kingY)
    {
        if (color == BLACK)
        {
            if (coordY + 1 < 8)
                if (board[coordY + 1][coordX].getType() == 'p' && board[coordY + 1][coordX].getColor() == color)
                    return true;
        }
        else
        {
            if (coordY - 1 >= 0)
                if (board[coordY - 1][coordX].getType() == 'P' && board[coordY - 1][coordX].getColor() == color)
                    return true;
        }
    }
    else if (coordX > kingX && coordY < kingY)
    {
        if (color == BLACK)
        {
            if (coordY + 1 < 8)
                if (board[coordY + 1][coordX].getType() == 'p' && board[coordY + 1][coordX].getColor() == color)
                    return true;
        }
        else
        {
            if (coordY - 1 >= 0)
                if (board[coordY - 1][coordX].getType() == 'P' && board[coordY - 1][coordX].getColor() == color)
                    return true;
        }
    }
    else if (coordX < kingX && coordY > kingY)
    {
        if (color == BLACK)
        {
            if (coordY + 1 < 8)
                if (board[coordY + 1][coordX].getType() == 'p' && board[coordY + 1][coordX].getColor() == color)
                    return true;
        }
        else
        {
            if (coordY - 1 >= 0)
                if (board[coordY - 1][coordX].getType() == 'P' && board[coordY - 1][coordX].getColor() == color)
                    return true;
        }
    }
    else if (coordX > kingX && coordY > kingY)
    {
        if (color == BLACK)
        {
            if (coordY + 1 < 8)
                if (board[coordY + 1][coordX].getType() == 'p' && board[coordY + 1][coordX].getColor() == color)
                    return true;
        }
        else
        {
            if (coordY - 1 >= 0)
                if (board[coordY - 1][coordX].getType() == 'P' && board[coordY - 1][coordX].getColor() == color)
                    return true;
        }
    }
    return false;
}


std::istream& operator>>(std::istream& is, Board& b)
{
    std::vector<Piece> line;
    char ch;
    int color;
    for (int i = 7; i >= 0; --i) {
        line.clear();
        for (int j = 0; j < 8; ++j)
        {
            is >> ch;
            if (ch < 'Z' && ch > 'A')
                color = 0;
            else if (ch < 'z' && ch > 'a')
                color = 1;
            if (ch == 'r' || ch == 'R')
                line.push_back(Piece(ch, color, j, i, 5));
            else if (ch == 'n' || ch == 'N')
                line.push_back(Piece(ch, color, j, i, 3));
            else if (ch == 'b' || ch == 'B')
                line.push_back(Piece(ch, color, j, i, 3));
            else if (ch == 'q' || ch == 'Q')
                line.push_back(Piece(ch, color, j, i, 9));
            else if (ch == 'k' || ch == 'K')
                line.push_back(Piece(ch, color, j, i, 0));
            else if (ch == 'p' || ch == 'P')
                line.push_back(Piece(ch, color, j, i, 1));
            else if (ch == '.')
                line.push_back(Piece(ch, -1, j, i, 0));
            else {
                std::cout << "The file contains unknown element" << std::endl;
                exit (-1);
            }
        }
        b.board[i] = line;
    }
    b.updateUnderAttack();
}


