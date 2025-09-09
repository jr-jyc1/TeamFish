#include "Game.h"
#include <iostream>
#include <algorithm>
#include <string>

Game::Game() : currentPlayerIndex(0) {
    setupPlayers();
}

void Game::setupPlayers() {
    // Player A1
    players[0] = {0, TEAM_A, WHITE};
    // Player B1
    players[1] = {1, TEAM_B, BLACK};
    // Player A2
    players[2] = {2, TEAM_A, WHITE};
    // Player B2
    players[3] = {3, TEAM_B, BLACK};
}

void Game::start(int argc, char* argv[]) {
    if (argc > 1) {
        // Test mode with a single move
        std::string moveStr = argv[1];

        board.printBoard();
        Player& currentPlayer = players[currentPlayerIndex];
        std::cout << "Current player: " << currentPlayer.id
                  << " (Team " << (currentPlayer.team == TEAM_A ? 'A' : 'B')
                  << ", " << (currentPlayer.color == WHITE ? "White" : "Black")
                  << ")" << std::endl;

        auto legalMoves = board.getLegalMoves(currentPlayer);
        std::cout << "Found " << legalMoves.size() << " legal moves." << std::endl;

        auto parseMove = [](const std::string& moveStr) {
            if (moveStr.length() != 4) return Move{-1,-1,-1,-1};
            int fromCol = moveStr[0] - 'a';
            int fromRow = 8 - (moveStr[1] - '0');
            int toCol = moveStr[2] - 'a';
            int toRow = 8 - (moveStr[3] - '0');
            return Move{fromRow, fromCol, toRow, toCol};
        };

        Move move = parseMove(moveStr);

        bool isValidMove = false;
        if (move.fromRow != -1) {
            for (auto& legalMove : legalMoves) {
                if (legalMove.fromRow == move.fromRow && legalMove.fromCol == move.fromCol &&
                    legalMove.toRow == move.toRow && legalMove.toCol == move.toCol) {
                    isValidMove = true;
                    board.makeMove(legalMove);
                    break;
                }
            }
        }

        if (isValidMove) {
            std::cout << "Making move: " << moveStr << std::endl;
            board.printBoard();
        } else {
            std::cout << "Invalid move: " << moveStr << std::endl;
        }
    } else {
        // Interactive mode
        gameLoop();
    }
}

bool Game::isCheckmate(const Player& player) {
    if (!board.isKingInCheck(player.id)) {
        return false;
    }
    std::vector<Move> legalMoves = board.getLegalMoves(player);
    return legalMoves.empty();
}

void Game::gameLoop() {
    auto parseMove = [](const std::string& moveStr) {
        if (moveStr.length() != 4) return Move{-1,-1,-1,-1};
        int fromCol = moveStr[0] - 'a';
        int fromRow = 8 - (moveStr[1] - '0');
        int toCol = moveStr[2] - 'a';
        int toRow = 8 - (moveStr[3] - '0');
        return Move{fromRow, fromCol, toRow, toCol};
    };

    while (true) {
        board.printBoard();
        Player& currentPlayer = players[currentPlayerIndex];
        std::cout << "Current player: " << currentPlayer.id
                  << " (Team " << (currentPlayer.team == TEAM_A ? 'A' : 'B')
                  << ", " << (currentPlayer.color == WHITE ? "White" : "Black")
                  << ")" << std::endl;

        auto legalMoves = board.getLegalMoves(currentPlayer);

        if (board.isKingInCheck(currentPlayer.id)) {
            std::cout << "You are in check!" << std::endl;
        }

        std::cout << "Found " << legalMoves.size() << " legal moves." << std::endl;
        std::cout << "Enter a move (e.g., e2e4), 'moves' to see legal moves, or 'exit': " << std::flush;
        std::string moveStr;
        std::cin >> moveStr;

        if (moveStr == "exit") {
            break;
        }

        if (moveStr == "moves") {
            for (const auto& m : legalMoves) {
                std::cout << (char)('a' + m.fromCol) << 8 - m.fromRow
                          << (char)('a' + m.toCol) << 8 - m.toRow << std::endl;
            }
            continue;
        }

        Move move = parseMove(moveStr);

        bool isValidMove = false;
        if (move.fromRow != -1) {
            for (auto& legalMove : legalMoves) {
                if (legalMove.fromRow == move.fromRow && legalMove.fromCol == move.fromCol &&
                    legalMove.toRow == move.toRow && legalMove.toCol == move.toCol) {
                    isValidMove = true;
                    board.makeMove(legalMove);
                    break;
                }
            }
        }

        if (isValidMove) {
            bool teamACheckmated = isCheckmate(players[0]) || isCheckmate(players[2]);
            bool teamBCheckmated = isCheckmate(players[1]) || isCheckmate(players[3]);

            if (teamACheckmated) {
                board.printBoard();
                std::cout << "Checkmate! Team B wins!" << std::endl;
                break;
            }
            if (teamBCheckmated) {
                board.printBoard();
                std::cout << "Checkmate! Team A wins!" << std::endl;
                break;
            }

            currentPlayerIndex = (currentPlayerIndex + 1) % 4;
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }
}
