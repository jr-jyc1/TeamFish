#include "Board.h"
#include "Player.h"
#include <utility>
#include <fstream>

Board::Board() {
    setupInitialPosition();
}

void Board::printBoard() {
    std::cout << "  a b c d e f g h" << std::endl;
    std::cout << " +-----------------" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << "|";
        for (int j = 0; j < 8; ++j) {
            char pieceChar = '.';
            switch (board[i][j].type) {
                case PAWN: pieceChar = 'p'; break;
                case KNIGHT: pieceChar = 'n'; break;
                case BISHOP: pieceChar = 'b'; break;
                case ROOK: pieceChar = 'r'; break;
                case QUEEN: pieceChar = 'q'; break;
                case KING: pieceChar = 'k'; break;
                case EMPTY: pieceChar = '.'; break;
            }
            if (board[i][j].color == WHITE) {
                pieceChar = toupper(pieceChar);
            }
            std::cout << pieceChar << " ";
        }
        std::cout << "|" << 8 - i << std::endl;
    }
    std::cout << " +-----------------" << std::endl;
    std::cout << "  a b c d e f g h" << std::endl;
}

void Board::loadPosition(const Piece new_board[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = new_board[i][j];
        }
    }
}

void Board::getKingMoves(int r, int c, std::vector<Move>& moves, const Player& player) {
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int newR = r + dr[i];
        int newC = c + dc[i];

        if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
            Piece target = board[newR][newC];
            if (target.type == EMPTY || target.color != player.color) {
                moves.push_back({r, c, newR, newC, target});
            }
        }
    }
}

void Board::getQueenMoves(int r, int c, std::vector<Move>& moves, const Player& player) {
    getRookMoves(r, c, moves, player);
    getBishopMoves(r, c, moves, player);
}

void Board::getBishopMoves(int r, int c, std::vector<Move>& moves, const Player& player) {
    int dr[] = {-1, -1, 1, 1};
    int dc[] = {-1, 1, -1, 1};

    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 8; ++j) {
            int newR = r + j * dr[i];
            int newC = c + j * dc[i];

            if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
                Piece target = board[newR][newC];
                if (target.type == EMPTY) {
                    moves.push_back({r, c, newR, newC, target});
                } else {
                    if (target.color != player.color) {
                        moves.push_back({r, c, newR, newC, target});
                    }
                    break;
                }
            } else {
                break;
            }
        }
    }
}

void Board::getRookMoves(int r, int c, std::vector<Move>& moves, const Player& player) {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 8; ++j) {
            int newR = r + j * dr[i];
            int newC = c + j * dc[i];

            if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
                Piece target = board[newR][newC];
                if (target.type == EMPTY) {
                    moves.push_back({r, c, newR, newC, target});
                } else {
                    if (target.color != player.color) {
                        moves.push_back({r, c, newR, newC, target});
                    }
                    break;
                }
            } else {
                break;
            }
        }
    }
}

void Board::getPawnMoves(int r, int c, std::vector<Move>& moves, const Player& player) {
    int direction = (player.color == WHITE) ? -1 : 1;
    int startRow = (player.color == WHITE) ? 6 : 1;

    if (r + direction >= 0 && r + direction < 8 && board[r + direction][c].type == EMPTY) {
        moves.push_back({r, c, r + direction, c, {EMPTY, WHITE, -1}});
    }

    if (r == startRow && board[r + direction][c].type == EMPTY && board[r + 2 * direction][c].type == EMPTY) {
        moves.push_back({r, c, r + 2 * direction, c, {EMPTY, WHITE, -1}});
    }

    if (r + direction >= 0 && r + direction < 8) {
        if (c > 0 && board[r + direction][c - 1].type != EMPTY && board[r + direction][c - 1].color != player.color) {
            moves.push_back({r, c, r + direction, c - 1, board[r + direction][c - 1]});
        }
        if (c < 7 && board[r + direction][c + 1].type != EMPTY && board[r + direction][c + 1].color != player.color) {
            moves.push_back({r, c, r + direction, c + 1, board[r + direction][c + 1]});
        }
    }
}

void Board::setupInitialPosition() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = {EMPTY, WHITE, -1};
        }
    }

    // Player A1 (White, ID 0): Queen's side
    board[7][0] = {ROOK, WHITE, 0};
    board[7][1] = {KNIGHT, WHITE, 0};
    board[7][2] = {BISHOP, WHITE, 0};
    board[7][3] = {QUEEN, WHITE, 0};
    for (int i = 0; i < 4; ++i) board[6][i] = {PAWN, WHITE, 0};

    // Player A2 (White, ID 2): King's side
    board[7][4] = {KING, WHITE, 2};
    board[7][5] = {BISHOP, WHITE, 2};
    board[7][6] = {KNIGHT, WHITE, 2};
    board[7][7] = {ROOK, WHITE, 2};
    for (int i = 4; i < 8; ++i) board[6][i] = {PAWN, WHITE, 2};

    // Player B1 (Black, ID 1): Queen's side
    board[0][0] = {ROOK, BLACK, 1};
    board[0][1] = {KNIGHT, BLACK, 1};
    board[0][2] = {BISHOP, BLACK, 1};
    board[0][3] = {QUEEN, BLACK, 1};
    for (int i = 0; i < 4; ++i) board[1][i] = {PAWN, BLACK, 1};

    // Player B2 (Black, ID 3): King's side
    board[0][4] = {KING, BLACK, 3};
    board[0][5] = {BISHOP, BLACK, 3};
    board[0][6] = {KNIGHT, BLACK, 3};
    board[0][7] = {ROOK, BLACK, 3};
    for (int i = 4; i < 8; ++i) board[1][i] = {PAWN, BLACK, 3};
}

std::pair<int, int> Board::findKing(int ownerId) const {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (board[r][c].type == KING && board[r][c].ownerId == ownerId) {
                return {r, c};
            }
        }
    }
    return {-1, -1};
}

bool Board::isSquareAttacked(int r, int c, PlayerColor attackerColor) const {
    int dr_n[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc_n[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int i = 0; i < 8; ++i) {
        int newR = r + dr_n[i];
        int newC = c + dc_n[i];
        if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
            Piece p = board[newR][newC];
            if (p.type == KNIGHT && p.color == attackerColor) return true;
        }
    }

    int pawnDir = (attackerColor == WHITE) ? 1 : -1;
    if (r - pawnDir >= 0 && r - pawnDir < 8) {
        if (c > 0) {
            Piece p = board[r - pawnDir][c - 1];
            if (p.type == PAWN && p.color == attackerColor) return true;
        }
        if (c < 7) {
            Piece p = board[r - pawnDir][c + 1];
            if (p.type == PAWN && p.color == attackerColor) return true;
        }
    }

    int dr_r[] = {-1, 1, 0, 0};
    int dc_r[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 8; ++j) {
            int newR = r + j * dr_r[i];
            int newC = c + j * dc_r[i];
            if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
                Piece p = board[newR][newC];
                if (p.type != EMPTY) {
                    if (p.color == attackerColor && (p.type == ROOK || p.type == QUEEN)) return true;
                    break;
                }
            } else break;
        }
    }

    int dr_b[] = {-1, -1, 1, 1};
    int dc_b[] = {-1, 1, -1, 1};
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 8; ++j) {
            int newR = r + j * dr_b[i];
            int newC = c + j * dc_b[i];
            if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
                Piece p = board[newR][newC];
                if (p.type != EMPTY) {
                    if (p.color == attackerColor && (p.type == BISHOP || p.type == QUEEN)) return true;
                    break;
                }
            } else break;
        }
    }

    int dr_k[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc_k[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for(int i = 0; i < 8; ++i) {
        int newR = r + dr_k[i];
        int newC = c + dc_k[i];
        if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
            Piece p = board[newR][newC];
            if (p.type == KING && p.color == attackerColor) return true;
        }
    }

    return false;
}

bool Board::isKingInCheck(int ownerId) {
    std::pair<int, int> kingPos = findKing(ownerId);
    if (kingPos.first == -1) return false;

    PlayerColor kingColor;
    if (ownerId == 0 || ownerId == 2) kingColor = WHITE;
    else kingColor = BLACK;

    return isSquareAttacked(kingPos.first, kingPos.second, kingColor == WHITE ? BLACK : WHITE);
}

void Board::getKnightMoves(int r, int c, std::vector<Move>& moves, const Player& player) {
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; ++i) {
        int newR = r + dr[i];
        int newC = c + dc[i];

        if (newR >= 0 && newR < 8 && newC >= 0 && newC < 8) {
            Piece target = board[newR][newC];
            if (target.type == EMPTY || target.color != player.color) {
                moves.push_back({r, c, newR, newC, target});
            }
        }
    }
}

std::vector<Move> Board::getLegalMoves(const Player& player) {
    std::vector<Move> pseudoLegalMoves;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece piece = board[r][c];
            if (piece.type != EMPTY && piece.ownerId == player.id) {
                switch (piece.type) {
                    case PAWN:
                        getPawnMoves(r, c, pseudoLegalMoves, player);
                        break;
                    case KNIGHT:
                        getKnightMoves(r, c, pseudoLegalMoves, player);
                        break;
                    case ROOK:
                        getRookMoves(r, c, pseudoLegalMoves, player);
                        break;
                    case BISHOP:
                        getBishopMoves(r, c, pseudoLegalMoves, player);
                        break;
                    case QUEEN:
                        getQueenMoves(r, c, pseudoLegalMoves, player);
                        break;
                    case KING:
                        getKingMoves(r, c, pseudoLegalMoves, player);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    std::vector<Move> legalMoves;
    for (auto& move : pseudoLegalMoves) {
        makeMove(move);

        int teammateId = -1;
        if (player.id == 0) teammateId = 2;
        else if (player.id == 2) teammateId = 0;
        else if (player.id == 1) teammateId = 3;
        else if (player.id == 3) teammateId = 1;

        if (!isKingInCheck(player.id) && !isKingInCheck(teammateId)) {
            legalMoves.push_back(move);
        }
        undoMove(move);
    }

    return legalMoves;
}

void Board::makeMove(Move& move) {
    move.capturedPiece = board[move.toRow][move.toCol];
    board[move.toRow][move.toCol] = board[move.fromRow][move.fromCol];
    board[move.fromRow][move.fromCol] = {EMPTY, WHITE, -1};
}

void Board::undoMove(const Move& move) {
    board[move.fromRow][move.fromCol] = board[move.toRow][move.toCol];
    board[move.toRow][move.toCol] = move.capturedPiece;
}
