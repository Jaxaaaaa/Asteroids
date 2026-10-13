#include "raylib.h"
#include "config.h"
#include "game.h"

void reset_game(Ship *ship, Missile missiles[], Asteroid asteroid[], int* score){
    init_ship(ship);
    ship->invincible_timer = INVINCIBLE_DURATION;
    *score = 0;
    for(int i = 0; i<MAX_MISSILE; i++){
        missiles[i].alive = false;
    }
    for(int i = 0; i<MAX_ASTEROIDS; i++){
        asteroid[i].alive = false;
    }
    for(int i = 0; i< 5; i++){
        init_asteroid(&asteroid[i], GetRandomValue(0,SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT), BIG);
    }
}
