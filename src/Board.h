#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Move.h"
#include "Player.h"
#include <iostream>
#include <vector>

class Board {
public:
    Board();
    void printBoard();
    void loadPosition(const Piece new_board[8][8]);
    void makeMove(Move& move);
    void undoMove(const Move& move);
    std::vector<Move> getLegalMoves(const Player& player);

private:
    Piece board[8][8];
    void setupInitialPosition();
    std::pair<int, int> findKing(int ownerId) const;

    // Move generation helpers
    void getPawnMoves(int r, int c, std::vector<Move>& moves, const Player& player);
    void getKnightMoves(int r, int c, std::vector<Move>& moves, const Player& player);
    void getBishopMoves(int r, int c, std::vector<Move>& moves, const Player& player);
    void getRookMoves(int r, int c, std::vector<Move>& moves, const Player& player);
    void getQueenMoves(int r, int c, std::vector<Move>& moves, const Player& player);
    void getKingMoves(int r, int c, std::vector<Move>& moves, const Player& player);

public:
    bool isKingInCheck(int ownerId);
    bool isSquareAttacked(int r, int c, PlayerColor attackerColor) const;
};

#endif // BOARD_H
