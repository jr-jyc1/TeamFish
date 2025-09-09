#ifndef PIECE_H
#define PIECE_H

enum PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    EMPTY
};

enum PlayerColor {
    WHITE,
    BLACK
};

struct Piece {
    PieceType type;
    PlayerColor color;
    int ownerId; // 0: A1, 1: B1, 2: A2, 3: B2
};

#endif // PIECE_H
