#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED
#include <stdbool.h>
#define MAX_ASTEROIDS 30

typedef enum{
    BIG, //40
    MEDIUM, //20
    SMALL, //10
}AsteroidSize;

typedef struct{
    float coord_x;
    float coord_y;
    float speed_x;
    float speed_y;
    float radius;
    bool alive;
    AsteroidSize size;
} Asteroid;

void init_asteroid(Asteroid *asteroid, float x, float y, AsteroidSize size);
void update_asteroid(Asteroid *asteroid);
void draw_asteroid(Asteroid asteroid);

#endif // ASTEROID_H_INCLUDED
