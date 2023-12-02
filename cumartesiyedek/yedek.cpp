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

int Board::moveRook(int oldX, int oldY, int newX, int newY)
{
    Piece& oldCell = board[oldY][oldX];
    Piece& newCell = board[newY][newX];
    Piece tmp = board[oldY][oldX];
    oldCell = Piece('.', -1, oldX, oldY, 0);
    newCell = tmp;
    return (1);
}

int Board::moveBishop(int oldX, int oldY, int newX, int newY)
{
    Piece& oldCell = board[oldY][oldX];
    Piece& newCell = board[newY][newX];
    Piece tmp = board[oldY][oldX];
    oldCell = Piece('.', -1, oldX, oldY, 0);
    newCell = tmp;
    return 1;
}

int Board::moveKnight(int oldX, int oldY, int newX, int newY)
