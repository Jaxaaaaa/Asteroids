#include "raylib.h"
#include "config.h"
#include "game.h"
#include "asteroid.h"

void reset_game(Ship *ship, Missile missiles[], Asteroid asteroid[], int* score, int *wave){
    init_ship(ship);
    ship->invincible_timer = INVINCIBLE_DURATION;
    *score = 0;
    *wave = 1;
    for(int i = 0; i<MAX_MISSILE; i++){
        missiles[i].alive = false;
    }
    spawn_wave(asteroid, START_ASTEROIDS);
}
