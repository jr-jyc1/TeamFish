#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"

struct Move {
    int fromRow, fromCol;
    int toRow, toCol;
    Piece capturedPiece;
};

#endif // MOVE_H
