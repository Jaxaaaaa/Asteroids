#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED
#include <stdbool.h>
#define MAX_ASTEROIDS 30

typedef struct{
    float coord_x;
    float coord_y;
    float speed_x;
    float speed_y;
    float radius;
    bool alive;
} Asteroid;

void init_asteroid(Asteroid *asteroid, float x, float y, float radius);
void update_asteroid(Asteroid *asteroid);
void draw_asteroid(Asteroid asteroid);

#endif // ASTEROID_H_INCLUDED
