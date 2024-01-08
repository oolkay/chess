#include "../lib/Board.hpp"
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
bool Board::validateMove(const std::string &input) const
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

// CHECKS IF THE PAWN CAN MOVE TO THE GIVEN CELL
bool Board::validatePawnMove(int oldX, int oldY, int newX, int newY) const
{
    const Piece& destCell = board[newY][newX];
    const Piece& currentPiece = board[oldY][oldX];
    const char type = destCell.getType();

    // WHITE PAWN
    if (currentPiece.getColor() == 0)
    {    
        // UP
        if (oldX == newX && newY == oldY + 1 && type == '.') {
            return true;
        }
        else if (oldX == newX && newY == oldY + 2 && oldY == 1 && type == '.') {
            if (board[oldY + 1][oldX].getType() == '.')
                return true;
        }

        // ATTACK UP RIGHT
        else if (newY == oldY + 1 && newX == oldX + 1 && type != '.') {
            return true;
        }
        // ATTACK UP LEFT
        else if (newY == oldY + 1 && newX == oldX - 1 && type != '.') {
            return true;
        }
    }
    // BLACK PAWN
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

// CHECKS IF THE ROOK CAN MOVE TO THE GIVEN CELL
bool Board::validateRookMove(int oldX, int oldY, int newX, int newY) const
{
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

// CHECKS IF THE BISHOP CAN MOVE TO THE GIVEN CELL
bool Board::validateBishopMove(int oldX, int oldY, int newX, int newY) const
{
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
                if (board[j][i].getType() != '.' && i > newX && j < newY)
                    return false;
            }
        }
        //moves down right
        else if (oldX < newX && oldY > newY)
        {
            for (i = oldX + 1, j = oldY - 1; i < newX && j > newY; i++, j--)
            {
                if (board[j][i].getType() != '.' && i < newX && j > newY)
                    return false;
            }
        }
        //moves down left
        else if (oldX > newX && oldY > newY)
        {
            for (i = oldX - 1, j = oldY - 1; i > newX && j > newY; i--, j--)
            {
                if (board[j][i].getType() != '.' && i > newX && j > newY)
                    return false;
            }
        }
        if (j != newY || i != newX)
            return false;
        return true;
    }
    return false;
}

// CHECKS IF THE KNIGHT CAN MOVE TO THE GIVEN CELL
bool Board::validateKnightMove(int oldX, int oldY, int newX, int newY) const
{
    if ((abs(oldX-newX) == 2 && abs(oldY-newY) == 1) || (abs(oldX-newX) == 1 && abs(oldY-newY) == 2))
        return true;
    return false;
}

// CHECKS IF THE KING CAN MOVE TO THE GIVEN CELL
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
    std::cout << "\n[It is check you need to protect your king!]\n";
    return false;
}

bool Board::isCheckmate(int color)
{
    if (isCheck(color) == 0)
        return false;
    Piece& king = getKing(color);
    if (king.getIsUnderAttack(color) == false)
        return false;

    //TRY ALL THE VALID MOVES OF GIVEN COLOR
    for (int i = 0; i < 64; ++i)
    {
        // EACH PIECE
        const Piece& piece = board[i/8][i%8];
        if (piece.getColor() == color)
        {
            unsigned int size = piece.getPossibleMovesSize();
            // EACH MOVE
            for (unsigned int k = 0; k < size; ++k)
            {
                std::string move = piece.getPossibleMoves(k);
                Piece tmp = board[move[3] - '1'][move[2] - 'a'];
                movePiece(move[0]-'a', move[1]-'1', move[2] - 'a', move[3] - '1');
                updateUnderAttack();
                if (isCheck(color) == false)
                {
                    undoMove(tmp, move[2] - 'a', move[3] - '1', move[0]-'a', move[1]-'1');
                    return false;
                }
                undoMove(tmp, move[2] - 'a', move[3] - '1', move[0]-'a', move[1]-'1');
            }
        }
    }
    return true;
}

bool Board::isCheck(int color)
{
    const Piece& king = getKing(color);
    if (color == WHITE) {
        if (king.getIsUnderAttackByBlack() == true)
            return true;
        return false;
    }
    else if (color == BLACK){
        if (king.getIsUnderAttackByWhite() == true)
            return true;
        return false;
    }
    return false;
}

// This function returns the king of the given color
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

// This function checks if there is a piece on given coordinates
bool Board::isTherePiece(int x, int y) const
{
    if (y < 0 || y > 7 || x < 0 || x > 7)
        return false;
    if (board[y][x].getType() != '.')
        return true;
    else
        return false;
    return false;
}

// This function updates the under attack cells of each piece
// This function updates the under attack cells of each piece
int Board::movePiece(int oldX, int oldY, int newX, int newY)
{
    Piece& oldCell = board[oldY][oldX];
    Piece& newCell = board[newY][newX];
    Piece tmp = board[newY][newX];

    //PAWN UPGRADE
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

// initializes the board
void Board::initBoard()
{
    //white pieces
    board[0][0] = Piece('R', 0, 0, 0, 5);
    board[0][1] = Piece('N', 0, 1, 0, 3);
    board[0][2] = Piece('B', 0, 2, 0, 3);
    board[0][3] = Piece('Q', 0, 3, 0, 9);
    board[0][4] = Piece('K', 0, 4, 0, 0);
    board[0][5] = Piece('B', 0, 5, 0, 3);
    board[0][6] = Piece('N', 0, 6, 0, 3);
    board[0][7] = Piece('R', 0, 7, 0, 5);
    for (int i = 0; i < 8; i++) {
        board[1][i] = Piece('P', 0, i, 1, 1);
    }
    //black pieces
    board[7][0] = Piece('r', 1, 0, 7, 5);
    board[7][1] = Piece('n', 1, 1, 7, 3);
    board[7][2] = Piece('b', 1, 2, 7, 3);
    board[7][3] = Piece('q', 1, 3, 7, 9);
    board[7][4] = Piece('k', 1, 4, 7, 0);
    board[7][5] = Piece('b', 1, 5, 7, 3);
    board[7][6] = Piece('n', 1, 6, 7, 3);
    board[7][7] = Piece('r', 1, 7, 7, 5);
    for (int i = 0; i < 8; i++) {
        board[6][i] = Piece('p', 1, i, 6, 1);
    }
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = Piece('.', -1, j, i, 0);
        }
    }
    Board::setTurn(0);
    updateUnderAttack();
}

std::string Board::intToString(int x, int y) const
{
    std::string str;
    str += x + 'a';
    str += y + '1';
    return str;
}

// Checks if the given pawn attacks some cell
// if attacks, sets the cell as under attack by the pawn
// and inserts the valid cell as a pawn's possible move
void Board::isPawnAttacks(Piece &p)
{
    int x = p.getX();
    int y = p.getY();
    if (p.getColor() == 0) {
        if (x + 1 < 8 && y + 1 < 8) {
            if (board[y + 1][x + 1].getColor() != 0)
                setAndInsert(board[y + 1][x + 1], p, WHITE);
        }
        if (x - 1 >= 0 && y + 1 < 8) {
            if (board[y + 1][x - 1].getColor() != 0)
                setAndInsert(board[y + 1][x - 1], p, WHITE);
        }
    }
    else if (p.getColor() == 1) {
        if (x + 1 < 8 && y - 1 >= 0) {
            if (board[y - 1][x + 1].getColor() != 1)
                setAndInsert(board[y - 1][x + 1], p, BLACK);
        }
        if (x - 1 >= 0 && y - 1 >= 0) {
            if (board[y - 1][x - 1].getColor() != 1)
                setAndInsert(board[y - 1][x - 1], p, BLACK);
        }
    }
}

// Checks if the given rook attacks some cell
// if attacks, sets the cell as under attack by the rook
// and inserts the valid cell as a rook's possible move
void Board::isRookAttacks(Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    //checks up
    for (int i = pieceY + 1; i < 8 ; i++) {
        setAndInsert(board[i][pieceX], p, pieceColor);
        if (board[i][pieceX].getType() != '.')
            break;
    }
    //checks down
    for (int i = pieceY - 1; i >= 0 ; i--) {
        setAndInsert(board[i][pieceX], p, pieceColor);
        if (board[i][pieceX].getType() != '.')
            break;
    }
    //checks right
    for (int i = pieceX + 1; i < 8 ; i++) {
        setAndInsert(board[pieceY][i], p, pieceColor);
        if (board[pieceY][i].getType() != '.')
            break;
    }
    //checks left
    for (int i = pieceX - 1; i >= 0 ; i--) {
        setAndInsert(board[pieceY][i], p, pieceColor);
        if (board[pieceY][i].getType() != '.')
            break;
    }
}


// Checks if the given bishop attacks some cell
// if attacks, sets the cell as under attack by the bishop
// and inserts the valid cell as a bishop's possible move
void Board::isBishopAttacks(Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    //checks up-right
    for (int i = pieceX + 1, j = pieceY + 1; i < 8 && j < 8 ; i++, j++)
    {
        setAndInsert(board[j][i], p, pieceColor);
        if (board[j][i].getType() != '.')
            break;   
    }
    //checks up-left
    for (int i = pieceX - 1, j = pieceY + 1; i >= 0 && j < 8 && board[j][i].getColor() != pieceColor; i--, j++)
    {
        setAndInsert(board[j][i], p, pieceColor);
        if (board[j][i].getType() != '.')
            break;
    }
    //checks down-right
    for (int i = pieceX + 1, j = pieceY - 1; i < 8 && j >= 0 && board[j][i].getColor() != pieceColor; i++, j--)
    {
        setAndInsert(board[j][i], p, pieceColor);
        if (board[j][i].getType() != '.')
            break;
    }
    //checks down-left
    for (int i = pieceX - 1, j = pieceY - 1; i >= 0 && j >= 0 && board[j][i].getColor() != pieceColor; i--, j--)
    {
        setAndInsert(board[j][i], p, pieceColor);
        if (board[j][i].getType() != '.')
            break;
    }
}

// Checks if the given knight attacks some cell
// if attacks, sets the cell as under attack by the knight
// and inserts the valid cell as a knight's possible move
void Board::isKnightAttacks(Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    //   ___
    //  |
    //  |    
    if (pieceX + 1 < 8 && pieceY + 2 < 8) {
        if (board[pieceY + 2][pieceX + 1].getColor() != pieceColor)
            setAndInsert(board[pieceY+2][pieceX+1], p, pieceColor);
    }
    //   ____
    //  |
    if (pieceX + 2 < 8 && pieceY + 1 < 8) {
        if (board[pieceY + 1][pieceX + 2].getColor() != pieceColor)
            setAndInsert(board[pieceY + 1][pieceX + 2], p, pieceColor);
    }
    //   ____
    //      |
    if (pieceX + 2 < 8 && pieceY - 1 >= 0) {
        if (board[pieceY - 1][pieceX + 2].getColor() != pieceColor)
            setAndInsert(board[pieceY - 1][pieceX + 2], p, pieceColor);
    }
    //   ___
    //      |
    //      |
    if (pieceX + 1 < 8 && pieceY - 2 >= 0) {
        if (board[pieceY - 2][pieceX + 1].getColor() != pieceColor)
            setAndInsert(board[pieceY - 2][pieceX + 1], p, pieceColor);
    }
    //      ___
    //      |
    //      |
    if (pieceX - 1 >= 0 && pieceY - 2 >= 0) {
        if (board[pieceY - 2][pieceX - 1].getColor() != pieceColor)
            setAndInsert(board[pieceY - 2][pieceX - 1], p, pieceColor);
    }
    //      ____
    //      |
    if (pieceX - 2 >= 0 && pieceY - 1 >= 0) {
        if (board[pieceY - 1][pieceX - 2].getColor() != pieceColor)
            setAndInsert(board[pieceY - 1][pieceX - 2], p, pieceColor);
    }
    //     |____
    if (pieceX - 2 >= 0 && pieceY + 1 < 8) {
        if (board[pieceY + 1][pieceX - 2].getColor() != pieceColor)
            setAndInsert(board[pieceY + 1][pieceX - 2], p, pieceColor);
    }
    //  |
    //  |
    //  |____
    if (pieceX - 1 >= 0 && pieceY + 2 < 8) {
        if (board[pieceY + 2][pieceX - 1].getColor() != pieceColor)
            setAndInsert(board[pieceY + 2][pieceX - 1], p, pieceColor);
    }
}

// Checks if the given queen attacks some cell
void Board::isQueenAttacks(Piece &p)
{
    isBishopAttacks(p);
    isRookAttacks(p);
}

// Checks if the given king attacks some cell
// if attacks, sets the cell as under attack by the king
// and inserts the valid cell as a king's possible move
void Board::isKingAttacks(Piece &p)
{
    int x = p.getX();
    int y = p.getY();
    const int pieceColor = p.getColor();
    //check up-left, up, up-right
    if (y + 1 < 8) {
        if (x - 1 >= 0) {
            if (board[y + 1][x - 1].getColor() != pieceColor)
                if (board[y + 1][x - 1].getIsUnderAttack(pieceColor) == false)
                    setAndInsert(board[y + 1][x - 1],p, pieceColor);
        }
        if (board[y + 1][x].getColor() != pieceColor)
            if (board[y + 1][x].getIsUnderAttack(pieceColor) == false)
                setAndInsert(board[y + 1][x], p, pieceColor);
        if (x + 1 < 8) {
            if (board[y + 1][x + 1].getColor() != pieceColor)
                if (board[y + 1][x + 1].getIsUnderAttack(pieceColor) == false)
                    setAndInsert(board[y + 1][x + 1],p, pieceColor);
        }
    }
    //check left, right
    if (x - 1 >= 0) {
        if (board[y][x - 1].getColor() != pieceColor)
            if (board[y][x - 1].getIsUnderAttack((pieceColor) % 2) == false)
                setAndInsert(board[y][x - 1],p, pieceColor);
    }
    if (x + 1 < 8) {
        if (board[y][x + 1].getColor() != pieceColor)
            if (board[y][x + 1].getIsUnderAttack(pieceColor) == false)
                setAndInsert(board[y][x + 1],p, pieceColor);
    }
    //check down-left, down, down-right
    if (y - 1 >= 0) {
        if (x - 1 >= 0) {
            if (board[y - 1][x - 1].getColor() != pieceColor)
                if (board[y - 1][x - 1].getIsUnderAttack(pieceColor) == false)
                    setAndInsert(board[y - 1][x - 1],p, pieceColor);
        }
        if (board[y - 1][x].getColor() != pieceColor) {
            if (board[y - 1][x].getIsUnderAttack(pieceColor) == false)
                setAndInsert(board[y - 1][x], p, pieceColor);
        }
        if (x + 1 < 8) {
            if (board[y - 1][x + 1].getColor() != pieceColor)
                if (board[y - 1][x + 1].getIsUnderAttack(pieceColor) == false)
                    setAndInsert(board[y - 1][x + 1], p, pieceColor);
        }
    }
}

// This function updates the underAttack of all the pieces
void Board::updateUnderAttack()
{
    for (int i = 0; i < 64; i++)
    {
        board[i / 8][i % 8].setIsUnderAttackByBlack(false);
        board[i / 8][i % 8].setIsUnderAttackByWhite(false);
        board[i / 8][i % 8].clearPiecesAttacks();
        board[i / 8][i % 8].clearPossibleMove();
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

// This function set the underAttack of victiimPiece
// and insert the valid moves to attackerPiece
void Board::setAndInsert(Piece &victimPiece, Piece &attackerPiece, int color)
{

    int x = attackerPiece.getX();
    int y = attackerPiece.getY();
    int attackerColor = attackerPiece.getColor();
    int victimColor = victimPiece.getColor();
    std::string coords;
    victimPiece.setIsUnderAttack(color, 1);
    victimPiece.insertPiecesAttack(attackerPiece);
    if (victimColor == attackerColor)
        return;

    // IF THE ATTACKER IS PAWN
    if (attackerPiece.getType() == 'P' || attackerPiece.getType() == 'p')
    {
        coords = attackerPiece.intToString(x, y);
        if (victimPiece.getType() != '.' && victimPiece.getColor() != attackerColor)
            attackerPiece.insertPossibleMove(coords + victimPiece.intToString(victimPiece.getX(), victimPiece.getY()));
        if (attackerColor == 0)
        {   if (attackerPiece.getY() == 1)
            {
                coords += intToString(x, y + 1);
                if (!isTherePiece(x, y + 1))
                    attackerPiece.insertPossibleMove(coords);
                coords.clear();
                coords += intToString(x, y);
                coords += intToString(x, y + 2);
                if (!isTherePiece(x, y + 2) && !isTherePiece(x, y + 1))
                    attackerPiece.insertPossibleMove(coords);
            }
            else
            {
                coords += intToString(x, y + 1);
                if (!isTherePiece(x, y + 1))
                    attackerPiece.insertPossibleMove(coords);
            }
        }
        else if (attackerColor == 1)
        {
            if (attackerPiece.getY() == 6)
            {
                coords += intToString(x, y - 1);
                if (!isTherePiece(x, y - 1))
                    attackerPiece.insertPossibleMove(coords);
                coords.clear();
                coords += intToString(x, y);
                coords += intToString(x, y - 2);
                if (!isTherePiece(x, y - 2) && !isTherePiece(x, y - 1))
                    attackerPiece.insertPossibleMove(coords);
            }
            else
            {
                coords += intToString(x, y - 1);
                if (!isTherePiece(x, y - 1))
                    attackerPiece.insertPossibleMove(coords);
            }
        }

    }
    else
    {
        coords += attackerPiece.getX() + 'a';
        coords += attackerPiece.getY() + '1';
        coords += victimPiece.getX() + 'a';
        coords += victimPiece.getY() + '1';
        attackerPiece.insertPossibleMove(coords);
    }
}


void Board::score()
{
    double whiteScore = getScore(WHITE);
    double blackScore = getScore(BLACK);
    std::cout << "White Score: " << whiteScore << std::endl;
    std::cout << "Black Score: " << blackScore << std::endl;        
}

double Board::getScore(int color)
{
    double score = 0;
    double pieceScore = 0;
    // color = color % 2;
    for (int i = 0; i < 64; ++i)
    {
        Piece& p = board[i / 8][i % 8];
        pieceScore = (double)p.getPoint();
        if (p.getColor() == color)
        {
            score += pieceScore - 0.5 * (double)p.getIsUnderAttack(color)*pieceScore;
        }
    }
    return score;
}

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    const std::vector< std::vector<Piece> > &b = board.board;
    os << std::endl;
    for (int i = 7; i >= 0; --i) {
        os << i + 1 << " | ";
        for (int j = 0; j < 8; j++)
            os << b[i][j].getType() << " ";
        os << std::endl;
    }
    os << "    ---------------" << std::endl;
    os << "    ";
    for (int i = 0; i < 8; i++)
        os << (char)('a' + i) << " ";
    return os;
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
        }
        b.board[i] = line;
    }
    b.updateUnderAttack();
    return is;
}

//suggest best move for the player
//trys all the possible moves and returns the best one
std::string Board::suggestMove(int color)
{
    double maxPoint = -1000;
    std::string bestMove;
    double allyP = getScore(color);
    double opponentP = getScore((color + 1) % 2);
    // iterate over all the pieces
    for (int i = 0; i < 64; ++i)
    {
        const Piece& piece = board[i/8][i%8];
        if (piece.getColor() == color)
        {
            unsigned int size = piece.getPossibleMovesSize();
            // iterate over all the valid moves of the piece
            for (unsigned int k = 0; k < size; ++k)
            {
                std::string move = piece.getPossibleMoves(k);
                Piece tmp = board[move[3] - '1'][move[2] - 'a'];
                movePiece(move[0]-'a', move[1]-'1', move[2] - 'a', move[3] - '1');
                updateUnderAttack();
                if (isCheck(color) == false)
                {
                    if (isCheckmate((color + 1) % 2) == true)
                    {
                        undoMove(tmp, move[2] - 'a', move[3] - '1', move[0]-'a', move[1]-'1');
                        return move;
                    }
                    if (board[move[3] - '1'][move[2] - 'a'].getIsUnderAttack(color) == true)
                    {
                        undoMove(tmp, move[2] - 'a', move[3] - '1', move[0]-'a', move[1]-'1');
                        continue;
                    }
                    allyP = getScore(color % 2);
                    opponentP = getScore((color + 1) % 2);
                    if (allyP - opponentP >= maxPoint)
                    {
                        maxPoint = allyP - opponentP;
                        bestMove = move;
                    }
                }
                undoMove(tmp, move[2] - 'a', move[3] - '1', move[0]-'a', move[1]-'1');
            }
        }
    }
    return bestMove;
}

