#include "raylib.h"
#include <math.h>
#include "config.h"
#include "asteroid.h"

void init_asteroid(Asteroid *asteroid, float x, float y, float radius){
    asteroid->coord_x = x;
    asteroid->coord_y = y;
    asteroid->radius = radius;
    float speed = GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED)
}
