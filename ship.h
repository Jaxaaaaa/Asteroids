#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

typedef struct{
    float coord_x;
    float coord_y;
    float speed_x;
    float speed_y;
    float view_angle;
    float radius;
    float acceleration;
    float rotation_speed;
    float slow_down_ratio;
} Ship;

void init_ship(Ship *ship);
void update_ship(Ship *ship);
void draw_ship(Ship ship);

#endif // SHIP_H_INCLUDED
