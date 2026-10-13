#include "raylib.h"
#include <math.h>
#include "config.h"
#include "asteroid.h"

const float radius_array[3] = { 40, 20, 10};

void init_asteroid(Asteroid *asteroid, float x, float y, AsteroidSize size){
    asteroid->coord_x = x;
    asteroid->coord_y = y;
    asteroid->size = size;
    asteroid->radius = radius_array[asteroid->size];
    float speed = GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED)/10.0f;
    int angle = GetRandomValue(0, 359);
    asteroid->speed_x = speed *  cos(angle*DEG2RAD);
    asteroid->speed_y = speed * sin(angle*DEG2RAD);
    asteroid->alive = true;
}

void update_asteroid(Asteroid *asteroid){
    asteroid->coord_x += asteroid->speed_x;
    asteroid->coord_y += asteroid->speed_y;
    if((asteroid->coord_x - asteroid->radius) > SCREEN_WIDTH){ //sortie de l'asteroid par la droite
        asteroid->coord_x = 0 - asteroid->radius;
    }
    if((asteroid->coord_x + asteroid->radius) < 0){ //sortie de l'asteroid par la gauche
        asteroid->coord_x = SCREEN_WIDTH + asteroid->radius;
    }
    if((asteroid->coord_y - asteroid->radius) > SCREEN_HEIGHT){ //sortie de l'asteroid par le bas
        asteroid->coord_y = 0 - asteroid->radius;
    }
    if((asteroid->coord_y + asteroid->radius) < 0){ //sortie de l'asteroid par le haut
        asteroid->coord_y = SCREEN_HEIGHT + asteroid->radius;
    }
}
void spawn_wave(Asteroid asteroid[], int number){
    for(int i = 0; i<MAX_ASTEROIDS; i++){
        asteroid[i].alive = false;
    }
    for(int i = 0; i< number && i<MAX_ASTEROIDS; i++){
        init_asteroid(&asteroid[i], GetRandomValue(0,SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT), BIG);
    }
}

bool any_asteroid_alive(Asteroid asteroid[]){
    for(int i = 0; i <MAX_ASTEROIDS; i++){
        if(asteroid[i].alive){
            return true;
        }
    }
    return false;
}

void draw_asteroid(Asteroid asteroid){
    DrawCircleLines((int)asteroid.coord_x, (int)asteroid.coord_y, asteroid.radius, WHITE);
}
