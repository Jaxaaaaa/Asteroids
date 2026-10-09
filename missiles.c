#include "raylib.h"
#include <math.h>
#include "config.h"
#include "missiles.h"

void init_missile(Missile *missile,Ship ship){
    float a = ship.view_angle * DEG2RAD; //l'angle du nez en radians
    float nose_x = ship.coord_x + cos(a) * ship.radius;
    float nose_y = ship.coord_y + sin(a) * ship.radius;
    missile->coord_x = nose_x;
    missile->coord_y = nose_y;
    missile->speed_x = MISSILE_SPEED * cos(a);
    missile->speed_y = MISSILE_SPEED * sin(a);
    missile->radius = MISSILE_RADIUS;
    missile->life_time = MISSILE_LIFE_TIME;
    missile->alive = true;
}

void update_missile(Missile *missile){
    missile->coord_x += missile->speed_x;
    missile->coord_y += missile->speed_y;
    if((missile->coord_x - missile->radius) > SCREEN_WIDTH){ //sortie du missile par la droite
        missile->alive = false;
    }
    if((missile->coord_x + missile->radius) < 0){ //sortie du missile par la gauche
        missile->alive = false;
    }
    if((missile->coord_y - missile->radius) > SCREEN_HEIGHT){ //sortie du missile par le bas
        missile->alive = false;
    }
    if((missile->coord_y + missile->radius) < 0){ //sortie du missile par le haut
        missile->alive = false;
    }
    missile->life_time--;
    if(missile->life_time <=0){
        missile->alive = false;
    }
}

void draw_missile(Missile missile){
    DrawCircleLines((int)missile.coord_x, (int)missile.coord_y, missile.radius, RED);
}
