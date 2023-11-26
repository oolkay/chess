#include "Board.hpp"
#include "Pieces.hpp"


// Default constructor
Board::Board()
{
    //creating two dimensional vector of size 8x8 refers to the board
    std::vector<std::vector<char> > board(8, std::vector<char>(8));

    //creating white pieces
    _wpieces.push_back(Pieces('R', 0, 'a'-'a', 5)); // 'a' - 'a' = 0
    _wpieces.push_back(Pieces('N', 0, 'b'-'a', 3)); // 'b' - 'a' = 1
    _wpieces.push_back(Pieces('B', 0, 'c'-'a', 3)); // 'c' - 'a' = 2
    _wpieces.push_back(Pieces('Q', 0, 'd'-'a', 9)); // 'd' - 'a' = 3
    _wpieces.push_back(Pieces('K', 0, 'e'-'a', 0)); 
    _wpieces.push_back(Pieces('B', 0, 'f'-'a', 3));
    _wpieces.push_back(Pieces('N', 0, 'g'-'a', 3));
    _wpieces.push_back(Pieces('R', 0, 'h'-'a', 5));
    for (int i = 0; i < 8; ++i)
        _wpieces.push_back(Pieces('P', 1, i, 1));

    //creating black pieces
    for (int i = 0; i < 8; ++i)
        _bpieces.push_back(Pieces('p', 6, i, 1));
    _bpieces.push_back(Pieces('r', 7, 'a'-'a', 5));
    _bpieces.push_back(Pieces('n', 7, 'b'-'a', 3));
    _bpieces.push_back(Pieces('b', 7, 'c'-'a', 3));
    _bpieces.push_back(Pieces('q', 7, 'd'-'a', 9));
    _bpieces.push_back(Pieces('k', 7, 'e'-'a', 0));
    _bpieces.push_back(Pieces('b', 7, 'f'-'a', 3));
    _bpieces.push_back(Pieces('n', 7, 'g'-'a', 3));
    _bpieces.push_back(Pieces('r', 7, 'h'-'a', 5));

    //filling the board with pieces
    for (int i = 0; i < 16 ; ++i)
        board[i / 8 + 6][i % 8] = _bpieces[i].getPieceType();
    for (int i = 2; i < 6 ; ++i)
        for (int j = 0; j < 8; ++j)
            board[i][j] = '.';
    for (int i = 0; i < 16 ; ++i)
        board[i / 8][i % 8] = _wpieces[i].getPieceType();
    _board = board;
}

// Copy constructor
Board::Board(const Board &rhs)
{
    *this = rhs;
}

// Assignment operator
Board &Board::operator=(const Board &rhs)
{
    if (this != &rhs)
    {
        this->_wpieces = rhs._wpieces;
        this->_bpieces = rhs._bpieces;
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8 ; ++j)
                this->_board[i][j] = rhs._board[i][j];
    }
    return *this;
}

// Destructor
Board::~Board()
{
}

// Prints the board
void Board::printBoard() const
{
}

// Updates the board
void Board::updateBoard(std::string move)
{
    Pieces p;
    int indx = 0;
    std::string piece = move.substr(0,2);
    std::string dest = move.substr(2,4);
    indx = whichPiece(piece);
    p = _wpieces[indx];
}

// Validates the only input FORMAT for ex: e5e6
bool Board::validateInputFormat(std::string move) const
{
    if (move.length() != 4 || move.empty())
        return false;
    std::string piece = move.substr(0,2); // e5
    std::string dest = move.substr(2,4); // e6
    if (piece[0] < 'a' || piece[0] > 'h' || piece[1] < '1' || piece[1] > '8')
        return false;
    if (dest[0] < 'a' || dest[0] > 'h' || dest[1] < '1' || dest[1] > '8')
        return false;
    if (isTherePiece(piece) == false)
        return false;
    return true;
}

// Validates the move
bool Board::validateAndMove(std::string move)
{
    int pieceIndx = 0;
    int oldLetter = move[0]-'a';
    int oldIndx = move[1] - 48 - 1;
    int destLetter = move[2]-'a';
    int destIndx = move[3] - 48 - 1;

    std::string dest = move.substr(2,4);
    pieceIndx = whichPiece(move.substr(0,2));
    Pieces& p = _wpieces[pieceIndx];
    if (p.getPieceType() == 'P')
    { 
        if (ValidatePawnMove(move))
        {
            p.setLetter(destLetter);
            p.setIndx(destIndx);
            _board[destIndx][destLetter] = 'P';
            _board[oldIndx][oldLetter] = '.';
        }
        return false;
    }
    if (p.getPieceType() == 'R')
    {
        if (ValidateRookMove(move))
        {
            p.setLetter(destLetter);
            p.setIndx(destIndx);
            _board[destIndx][destLetter] = 'R';
            _board[oldIndx][oldLetter] = '.';
        }
        return false;
    }
    
    return true;
}

int Board::isTherePiece(std::string coord) const
{
    if (_board[coord[1] - 48 - 1][coord[0] -'a'] == '.')
        return -1;
    if (_board[coord[1] - 48 - 1][coord[0] -'a'] < 'Z' && _board[coord[1] - 48 - 1][coord[0] -'a'] > 'A')
        return (1);
    if (_board[coord[1] - 48 - 1][coord[0] -'a'] < 'z' && _board[coord[1] - 48 - 1][coord[0] -'a'] > 'a')
        return (2);
    return (-1);
}

bool Board::ValidatePawnMove(const std::string &move) const
{
    std::string oldCell = move.substr(0,2);
    std::string destCell = move.substr(2,4);
    int destLetter = destCell[0]-'a';
    int destIndx = destCell[1] - 48 - 1;
    int oldLetter = oldCell[0]-'a';
    int oldIndx = oldCell[1] - 48 - 1;
    if (destLetter == oldLetter && destIndx == oldIndx + 1)
        return true;
    if (destLetter == oldLetter && destIndx == oldIndx + 2)
        if (oldIndx == 1)
            return true;
    if (destLetter == oldLetter + 1 && destIndx == oldIndx + 1
            || destLetter == oldLetter - 1 && destIndx == oldIndx + 1)
        if (isTherePiece(destCell) == 2)
            return true;
    return false;
}

bool Board::ValidateBishopMove(const std::string &move) const
{
    std::string oldCell = move.substr(0,2);
    std::string destCell = move.substr(2,4);
    int destLetter = destCell[0]-'a';
    int destIndx = destCell[1] - 48 - 1;
    int oldLetter = oldCell[0]-'a';
    int oldIndx = oldCell[1] - 48 - 1;
    if (destLetter == oldLetter || destIndx == oldIndx)
        return false;
    if (destLetter > oldLetter && destIndx > oldIndx)
    {
        for (int i = oldIndx + 1, j = oldLetter + 1; i < destIndx && j < destLetter; ++i, ++j)
            if (_board[i][j] != '.')
                return false;
    }
    if (destLetter > oldLetter && destIndx < oldIndx)
    {
        for (int i = oldIndx - 1, j = oldLetter + 1; i > destIndx && j < destLetter; --i, ++j)
            if (_board[i][j] != '.')
                return false;
    }
    if (destLetter < oldLetter && destIndx > oldIndx)
    {
        for (int i = oldIndx + 1, j = oldLetter - 1; i < destIndx && j > destLetter; ++i, --j)
            if (_board[i][j] != '.')
                return false;
    }
}

bool Board::ValidateRookMove(const std::string &move) const
{
    std::string oldCell = move.substr(0,2);
    std::string destCell = move.substr(2,4);
    int destLetter = destCell[0]-'a';
    int destIndx = destCell[1] - 48 - 1;
    int oldLetter = oldCell[0]-'a';
    int oldIndx = oldCell[1] - 48 - 1;
    if (destLetter == oldLetter && destIndx != oldIndx && destIndx <= 8 && destIndx >= 0)
    {
        if (destIndx > oldIndx)
        {
            for (int i = oldIndx + 1; i < destIndx; ++i)
                if (_board[i][oldLetter] != '.')
                    return false;
        }
        else
        {
            for (int i = oldIndx - 1; i > destIndx; --i)
                if (_board[i][oldLetter] != '.')
                    return false;
        }
        return true;
    }
    if (destLetter != oldLetter && destIndx == oldIndx && destLetter <= 'h' && destLetter >= 'a')
    {
        if (destLetter > oldLetter)
        {
            for (int i = oldLetter + 1; i < destLetter; ++i)
                if (_board[oldIndx][i] != '.')
                    return false;
        }
        else
        {
            for (int i = oldLetter - 1; i > destLetter; --i)
                if (_board[oldIndx][i] != '.')
                    return false;
        }
        return true;
    }
    return false;
}


int Board::whichPiece(std::string coord) const
{
    char pieceType;
    for (int i = 0; i < 16; ++i)
    {
        if (_wpieces[i].getLetter() == coord[0]-'a' && _wpieces[i].getIndx() == coord[1] -48 - 1)
            return i;
    }
    return (-1);
}

std::ostream &operator<<(std::ostream &os, const Board &rhs)
{
    for (int i = 7; i >= 0; --i)
    {
        os << i + 1 << " | ";
        for (int j = 0; j < 8; ++j)
            os << rhs._board[i][j] << " ";
        os << std::endl;
    }
    os << "    ";
    for (int i = 0; i < 8; ++i)
        os << (char)('a' + i) << " ";
    os << std::endl;
    return os;
}

/*tehdit algoritması
önünde, dikeyinde, yatayında, çarparzında taş var mı bide lsinde
hangi taş var
tehdit mi
her movedan sonra bütün piecelere uygula
*/
