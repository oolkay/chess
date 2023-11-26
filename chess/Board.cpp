#include "Board.hpp"
#include "Pieces.hpp"


// Default constructor
Board::Board()
{
    //creating two dimensional vector of size 8x8 refers to the board
    std::vector<std::vector<char>> board(8, std::vector<char>(8));

    //creating white pieces
    _wpieces.push_back(Pieces('R', 0, 0, 5));
    _wpieces.push_back(Pieces('N', 0, 1, 3));
    _wpieces.push_back(Pieces('B', 0, 2, 3));
    _wpieces.push_back(Pieces('Q', 0, 3, 9));
    _wpieces.push_back(Pieces('K', 0, 4, 0));
    _wpieces.push_back(Pieces('B', 0, 5, 3));
    _wpieces.push_back(Pieces('N', 0, 6, 3));
    _wpieces.push_back(Pieces('R', 0, 7, 5));
    for (int i = 0; i < 8; ++i)
        _wpieces.push_back(Pieces('P', 1, i, 1));

    //creating black pieces
    for (int i = 0; i < 8; ++i)
        _bpieces.push_back(Pieces('p', 6, i, 1));
    _bpieces.push_back(Pieces('r', 7, 0, 5));
    _bpieces.push_back(Pieces('n', 7, 1, 3));
    _bpieces.push_back(Pieces('b', 7, 2, 3));
    _bpieces.push_back(Pieces('q', 7, 3, 9));
    _bpieces.push_back(Pieces('k', 7, 4, 0));
    _bpieces.push_back(Pieces('b', 7, 5, 3));
    _bpieces.push_back(Pieces('n', 7, 6, 3));
    _bpieces.push_back(Pieces('r', 7, 7, 5));

    //filling the board with pieces
    for (int i = 0; i < 16 ; ++i)
        board[i / 8][i % 8] = _wpieces[i].getPieceType();
    for (int i = 2; i < 6 ; ++i)
        for (int j = 0; j < 8; ++j)
            board[i][j] = '.';
    for (int i = 0; i < 16 ; ++i)
        board[i / 8 + 6][i % 8] = _bpieces[i].getPieceType();
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
    for (int i = 7; i >= 0; --i)
    {
        std::cout << i + 1 << " ";
        for (int j = 7; j >= 0; --j)
            std::cout << _board[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << "  ";
    for (int i = 0; i < 8; ++i)
        std::cout << (char)('a' + i) << " ";
    std::cout << std::endl;
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

// Validates the input format for ex: e5e6
bool Board::validateInputFormat(std::string move) const
{
    if (move.length() != 4 || move.empty())
        return false;
    std::string piece = move.substr(0,2);
    std::string dest = move.substr(2,4);
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
    Pieces p;
    int indx = 0;
    std::string piece = move.substr(0,2);
    std::string dest = move.substr(2,4);
    if (piece[0] == dest[0] && piece[1] == dest[1])
        return false;
    //e2-->4 2
    indx = whichPiece(piece);
    p = _wpieces[indx];
    if (p.getPieceType() == 'P')
    {
        if (p.getLetter() + 'a' == dest[0] && isTherePiece(dest))
            return false;
        if (p.getLetter() + 'a' != dest[0] && !isTherePiece(dest))
            return false;
        if (p.getLetter() + 'a' != dest[0] && isTherePiece(dest))
        {
            if (p.getLetter() + 'a' + 1 != dest[0] && p.getLetter() + 'a' - 1 != dest[0])
                return false;
        }
        _board[p.getIndx()][p.getLetter()] = '.';
        _wpieces[indx].setIndx(dest[1] - 48);
        _wpieces[indx].setLetter(dest[0] - 'a');
    }
    return true;
}

bool Board::isTherePiece(std::string coord) const
{
    if (_board[coord[0] -'a'][coord[1] - 48] != '.')
        return true;
    return false;
}

int Board::whichPiece(std::string coord) const
{
    char pieceType;
    for (int i = 0; i < 16; ++i)
        if (_wpieces[i].getIndx() == coord[0] && _wpieces[i].getLetter() == coord[1])
            return (i);
    return (-1);
}

/*tehdit algoritması
önünde, dikeyinde, yatayında, çarparzında taş var mı bide lsinde
hangi taş var
tehdit mi
her movedan sonra bütün piecelere uygula
*/
