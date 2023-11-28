#include "../libraries/Board.hpp"

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
        return false;
    std::string piece = input.substr(0,2); // e2
    std::string dest = input.substr(2,4); // e4
    if (piece[0] < 'a' || piece[0] > 'h' || piece[1] < '1' || piece[1] > '8')
        return false;
    if (dest[0] < 'a' || dest[0] > 'h' || dest[1] < '1' || dest[1] > '8')
        return false;
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
        return false;
    // trying to eat same color
    if (isTherePiece(newX, newY) == true)
    {
        if (board[newY][newX].getColor() == p.getColor())
            return false;
    }
    
    // if white's turn, check if the piece is white
    //todo: error msga1
    if (turn % 2 == 0)
    {
        if (p.getColor() == 1)
            return false;
    }
    // if black's turn, check if the piece is 
    else
    {
        if (p.getColor() == 0)
            return false;
    }

    /*CHECK WHICH PIECE*/
    if (pieceType == 'P' || pieceType == 'p')
    {
        if (validatePawnMove(oldX, oldY, newX, newY))
        {
            movePiece(oldX, oldY, newX, newY);
        }
        else
            return false;
    }
    else if (pieceType == 'R' || pieceType == 'r')
    {

        if (validateRookMove(oldX, oldY, newX, newY))
            movePiece(oldX, oldY, newX, newY);
        else
            return false;
    }
    else if (pieceType == 'B' || pieceType == 'b')
    {
        if (validateBishopMove(oldX, oldY, newX, newY))
            movePiece(oldX, oldY, newX, newY);
        else
            return false;
    }
    else if (pieceType == 'N' || pieceType == 'n')
    {
        if (validateKnightMove(oldX, oldY, newX, newY))
            movePiece(oldX, oldY, newX, newY);
        else
            return false;
    }
    else if (pieceType == 'Q' || pieceType == 'q')
    {
        if (validateBishopMove(oldX, oldY, newX, newY))
            movePiece(oldX, oldY, newX, newY);
        else if (validateRookMove(oldX, oldY, newX, newY))
            movePiece(oldX, oldY, newX, newY);
        else
            return false;
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
        // if (destCell.getType() != '.')
        // {
        //     if (destCell.getColor() == 0 && turn % 2 == 0)
        //         return false;
        //     else if (destCell.getColor() == 1 && turn % 2 == 1)
        //         return false;
        // }
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
        // if (destCell.getType() != '.')
        // {
        //     if (destCell.getColor() == 0 && turn % 2 == 0)
        //         return false;
        //     else if (destCell.getColor() == 1 && turn % 2 == 1)
        //         return false;
        // }
        return true;
    }
    return true;
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
    const Piece& destCell = board[newY][newX];
    
    //   ___
    //  |
    //  |    
    if (newX == oldX + 1 && newY == oldY + 2)
        return true;
    //   ____
    //  |
    else if (newX == oldX + 2 && newY == oldY + 1)
        return true;
    //   ____
    //      |
    else if (newX == oldX + 2 && newY == oldY - 1)
        return true;
    //   ___
    //      |
    //      |
    else if (newX == oldX + 1 && newY == oldY - 2)
        return true;
    //      ___
    //      |
    //      |
    else if (newX == oldX - 1 && newY == oldY - 2)
        return true;
    //      ____
    //      |
    else if (newX == oldX - 2 && newY == oldY - 1)
        return true;
    //     |____
    else if (newX == oldX - 2 && newY == oldY + 1)
        return true;
    //  |
    //  |
    //  |____
    else if (newX == oldX - 1 && newY == oldY + 2)
        return true;
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


/*TODO TEK BİR MOVE FONKSİYONU MOVE PİECE*/
int Board::movePiece(int oldX, int oldY, int newX, int newY)
{
    Piece& oldCell = board[oldY][oldX];
    Piece& newCell = board[newY][newX];
    newCell.setType(oldCell.getType());
    newCell.setColor(oldCell.getColor());
    newCell.setPoint(oldCell.getPoint());
    oldCell.setType('.');
    oldCell.setColor(-1);
    oldCell.setPoint(0);
    return (1);
}

void Board::setTurn(int turn)
{
    Board::turn = turn;
}

void Board::isPawnAttacks(const Piece &p)
{
    if (p.getColor() == 0)
    {
        if (p.getX() + 1 < 8 && p.getY() + 1 < 8) {
            if (board[p.getY() + 1][p.getX() + 1].getColor() == 1)
            {
                board[p.getY() + 1][p.getX() + 1].setIsUnderAttack(true);
            }
        }
        if (p.getX() - 1 >= 0 && p.getY() + 1 < 8) {
            if (board[p.getY() + 1][p.getX() - 1].getColor() == 1)
                board[p.getY() + 1][p.getX() - 1].setIsUnderAttack(true);
        }
    }
    else if (p.getColor() == 1)
    {
        if (p.getX() + 1 < 8 && p.getY() - 1 >= 0) {
            if (board[p.getY() - 1][p.getX() + 1].getColor() == 0)
                board[p.getY() - 1][p.getX() + 1].setIsUnderAttack(true);
        }
        if (p.getX() - 1 >= 0 && p.getY() - 1 >= 0) {
            if (board[p.getY() - 1][p.getX() - 1].getColor() == 0)
            {
                board[p.getY() - 1][p.getX() - 1].setIsUnderAttack(true);
            }
        }
    }
}

void Board::isRookAttacks(const Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    //checks up
    for (int i = pieceY + 1; i < 8; i++)
    {
        if (board[i][pieceX].getType() != '.')
        {
            if (board[i][pieceX].getColor() != pieceColor)
                board[i][pieceX].setIsUnderAttack(true);
            if (board[i][pieceX].getColor() == pieceColor)
                break;
        }
    }
    //checks down
    for (int i = pieceY - 1; i >= 0; i--)
    {
        if (board[i][pieceX].getType() != '.')
        {
            if (board[i][pieceX].getColor() != pieceColor)
                return board[i][pieceX].setIsUnderAttack(true);
            if (board[i][pieceX].getColor() == pieceColor)
                break;
        }
    }
    //checks right
    for (int i = pieceX + 1; i < 8; i++)
    {
        if (board[pieceY][i].getType() != '.')
        {
            if (board[pieceY][i].getColor() != pieceColor)
                board[pieceY][i].setIsUnderAttack(true);
            if (board[pieceY][i].getColor() == pieceColor)
                break;
        }
    }
    //checks left
    for (int i = pieceX - 1; i >= 0; i--)
    {
        if (board[pieceY][i].getType() != '.')
        {
            if (board[pieceY][i].getColor() != pieceColor)
                board[pieceY][i].setIsUnderAttack(true);
            if (board[pieceY][i].getColor() == pieceColor)
                break;
        }
    }
}

void Board::isBishopAttacks(const Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    //checks up-right
    for (int i = pieceX + 1, j = pieceY + 1; i < 8 && j < 8; i++, j++)
    {
        if (board[j][i].getType() != '.')
        {
            if (board[j][i].getColor() != pieceColor)
                board[j][i].setIsUnderAttack(true);
            if (board[j][i].getColor() == pieceColor)
                break;
        }
    }
    //checks up-left
    for (int i = pieceX - 1, j = pieceY + 1; i >= 0 && j < 8; i--, j++)
    {
        if (board[j][i].getType() != '.')
        {
            if (board[j][i].getColor() != pieceColor)
                board[j][i].setIsUnderAttack(true);
            if (board[j][i].getColor() == pieceColor)
                break;
        }
    }
    //checks down-right
    for (int i = pieceX + 1, j = pieceY - 1; i < 8 && j >= 0; i++, j--)
    {
        if (board[j][i].getType() != '.')
        {
            if (board[j][i].getColor() != pieceColor)
                board[j][i].setIsUnderAttack(true);
            if (board[j][i].getColor() == pieceColor)
                break;
        }
    }
    //checks down-left
    for (int i = pieceX - 1, j = pieceY - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (board[j][i].getType() != '.')
        {
            if (board[j][i].getColor() != pieceColor)
                board[j][i].setIsUnderAttack(true);
            if (board[j][i].getColor() == pieceColor)    
                break;
        }
    }
}

void Board::isKnightAttacks(const Piece &p)
{
    int pieceColor = p.getColor();
    int pieceX = p.getX();
    int pieceY = p.getY();
    if (p.getX() == 5 && p.getY() == 5)
    {
        std::cout <<"\n\n" << p << "\n\n";
        std::cout <<"\n\n" << board[pieceY - 2][pieceX - 1]<< "\n\n";

    }
    //   ___
    //  |
    //  |    
    if (pieceX + 1 < 8 && pieceY + 2 < 8) {
        if (board[pieceY + 2][pieceX + 1].getColor() != pieceColor &&
                 board[pieceY + 2][pieceX + 1].getType() != '.') {
            board[pieceY + 2][pieceX + 1].setIsUnderAttack(true);
        }
    }
    //   ____
    //  |
    else if (pieceX + 2 < 8 && pieceY + 1 < 8) {
        if (board[pieceY + 1][pieceX + 2].getColor() != pieceColor &&
                 board[pieceY + 1][pieceX + 2].getType() != '.') {
            board[pieceY + 1][pieceX + 2].setIsUnderAttack(true);
        }
    }
    //   ____
    //      |
    else if (pieceX + 2 < 8 && pieceY - 1 >= 0) {
        if (board[pieceY - 1][pieceX + 2].getColor() != pieceColor && 
                board[pieceY - 1][pieceX + 2].getType() != '.') {
            board[pieceY - 1][pieceX + 2].setIsUnderAttack(true);
        }
    }
    //   ___
    //      |
    //      |
    else if (pieceX + 1 < 8 && pieceY - 2 >= 0) {
        if (board[pieceY - 2][pieceX + 1].getColor() != pieceColor &&
                 board[pieceY - 2][pieceX + 1].getType() != '.') {
            board[pieceY - 2][pieceX + 1].setIsUnderAttack(true);
        }
    }
    //      ___
    //      |
    //      |
    else if (pieceX - 1 >= 0 && pieceY - 2 >= 0) {
        if (board[pieceY - 2][pieceX - 1].getColor() != pieceColor &&
                 board[pieceY - 2][pieceX - 1].getType() != '.') {
            board[pieceY - 2][pieceX - 1].setIsUnderAttack(true);
        }
    }
    //      ____
    //      |
    else if (pieceX - 2 >= 0 && pieceY - 1 >= 0) {
        if (board[pieceY - 1][pieceX - 2].getColor() != pieceColor &&
                 board[pieceY - 1][pieceX - 2].getType() != '.') {
            board[pieceY - 1][pieceX - 2].setIsUnderAttack(true);
        }
    }
    //     |____
    else if (pieceX - 2 >= 0 && pieceY + 1 < 8) {
        if (board[pieceY + 1][pieceX - 2].getColor() != pieceColor &&
                 board[pieceY + 1][pieceX - 2].getType() != '.') {
            board[pieceY + 1][pieceX - 2].setIsUnderAttack(true);
        }
    }
    //  |
    //  |
    //  |____
    else if (pieceX - 1 >= 0 && pieceY + 2 < 8) {
        if (board[pieceY + 2][pieceX - 1].getColor() != pieceColor &&
                 board[pieceY + 2][pieceX - 1].getType() != '.') {
            board[pieceY + 2][pieceX - 1].setIsUnderAttack(true);
        }
    }
}

void Board::isQueenAttacks(const Piece &p)
{
    isBishopAttacks(p);
    isRookAttacks(p);
}

void Board::updateUnderAttack()
{
    for (int i = 0; i < 64; i++)
        board[i / 8][i % 8].setIsUnderAttack(false);
    
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Piece& p = board[i][j];
            if ((p.getType() == 'P' || p.getType() == 'p'))
            {
                isPawnAttacks(p);
            }
            else if ((p.getType() == 'R' || p.getType() == 'r'))
            {
                isRookAttacks(p);
            }
            else if ((p.getType() == 'B' || p.getType() == 'b'))
            {
                isBishopAttacks(p);
            }
            else if ((p.getType() == 'N' || p.getType() == 'n'))
            {
                isKnightAttacks(p);
            }
            else if ((p.getType() == 'Q' || p.getType() == 'q'))
            {
                isQueenAttacks(p);
            }
            // else if ((p.getType() == 'K' || p.getType() == 'k'))
            // {
            //     Piece& pieceGetsAttacked = isKingAttacks(p);
            //     if (!(pieceGetsAttacked == p))
            //         pieceGetsAttacked.setIsUnderAttack(true);
            // }
        }
    }
}

void Board::score()
{
    double whiteScore = 0;
    double blackScore = 0;
    double pieceScore = 0;
    updateUnderAttack();//this function will update the isUnderAttack of each piece
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Piece& p = board[i][j];
            pieceScore = (double)p.getPoint();
            if (p.getColor() == 0)
            {
                whiteScore += pieceScore - 0.5 * (double)p.getIsUnderAttack()*pieceScore;
            }
            else if (p.getColor() == 1)
            {
                blackScore += pieceScore - 0.5 * (double)p.getIsUnderAttack()*pieceScore;

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
    return os;
}