#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game {
public:
    Game();
    void start(int argc, char* argv[]);

private:
    Board board;
    Player players[4];
    int currentPlayerIndex;

    void setupPlayers();
    void gameLoop();
    bool isCheckmate(const Player& player);
};

#endif // GAME_H
