#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"

enum Team {
    TEAM_A,
    TEAM_B
};

struct Player {
    int id;
    Team team;
    PlayerColor color;
};

#endif // PLAYER_H
