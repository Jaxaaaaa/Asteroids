#ifndef MISSILES_H_INCLUDED
#define MISSILES_H_INCLUDED
#include <stdbool.h>
#include "ship.h"
#define MAX_MISSILE 30
typedef struct{
    float coord_x;
    float coord_y;
    float speed_x;
    float speed_y;
    float radius;
    bool alive;
    int life_time;

} Missile;

void init_missile(Missile *missile,Ship ship);
void update_missile(Missile *missile);
void draw_missile(Missile missile);
#endif // MISSILES_H_INCLUDED
