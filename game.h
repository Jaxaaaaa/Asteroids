#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "ship.h"
#include "missiles.h"
#include "asteroid.h"
typedef enum{
    STATE_TITLE,
    STATE_PLAYING,
    STATE_GAME_OVER,
} State;

void reset_game(Ship *ship, Missile missiles[], Asteroid asteroid[], int *score);
#endif // GAME_H_INCLUDED
