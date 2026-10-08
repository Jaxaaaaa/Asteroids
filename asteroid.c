#include "raylib.h"
#include <math.h>
#include "config.h"
#include "asteroid.h"

void init_asteroid(Asteroid *asteroid, float x, float y, float radius){
    asteroid->coord_x = x;
    asteroid->coord_y = y;
    asteroid->radius = radius;
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

void draw_asteroid(Asteroid asteroid){
    DrawCircleLines((int)asteroid.coord_x, (int)asteroid.coord_y, asteroid.radius, WHITE);
}
