#include "test_board.h"
#include "../src/Board.h"
#include "../src/Player.h"
#include "../src/Game.h"
#include <cassert>

void test_starting_position() {
    Board b;
    Player p = {0, TEAM_A, WHITE};
    auto moves = b.getLegalMoves(p);
    assert(moves.size() == 10);
}

void test_checkmate() {
    Board b;
    Piece checkmate_board[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            checkmate_board[i][j] = {EMPTY, WHITE, -1};
        }
    }
    checkmate_board[7][7] = {KING, WHITE, 0};
    checkmate_board[6][7] = {QUEEN, BLACK, 1};
    checkmate_board[6][6] = {ROOK, BLACK, 1};

    b.loadPosition(checkmate_board);

    Player p = {0, TEAM_A, WHITE};
    auto moves = b.getLegalMoves(p);
    assert(moves.size() == 0);
    assert(b.isKingInCheck(0));
}

void test_no_friendly_fire_check() {
    Board b;
    Piece test_board[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            test_board[i][j] = {EMPTY, WHITE, -1};
        }
    }
    test_board[7][0] = {KING, WHITE, 0};
    test_board[7][4] = {KING, WHITE, 2};
    test_board[6][3] = {ROOK, WHITE, 0};
    test_board[5][4] = {QUEEN, BLACK, 1};

    b.loadPosition(test_board);

    Player p0 = {0, TEAM_A, WHITE};
    auto moves = b.getLegalMoves(p0);

    bool found_illegal_move = false;
    for (const auto& move : moves) {
        if (move.fromRow == 6 && move.fromCol == 3 && move.toRow == 6 && move.toCol == 2) {
            found_illegal_move = true;
            break;
        }
    }
    assert(!found_illegal_move);
}

void test_stalemate() {
    Board b;
    Piece stalemate_board[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            stalemate_board[i][j] = {EMPTY, WHITE, -1};
        }
    }
    stalemate_board[7][7] = {KING, WHITE, 0};
    stalemate_board[5][6] = {QUEEN, BLACK, 1};

    b.loadPosition(stalemate_board);

    Player p = {0, TEAM_A, WHITE};
    auto moves = b.getLegalMoves(p);
    assert(moves.size() == 0);
    assert(!b.isKingInCheck(0));
}
