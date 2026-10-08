#include "raylib.h"
#include <math.h>
#include "config.h"
#include "ship.h"

void init_ship(Ship* ship){
    ship->coord_x = (SCREEN_WIDTH/2);
    ship->coord_y = (SCREEN_HEIGHT/2);
    ship->radius = 10.0;
    ship->view_angle = -90;
    ship->acceleration = 0.1;
    ship->speed_x = 0;
    ship->speed_y = 0;
    ship->rotation_speed = 4;
    ship->slow_down_ratio = 0.95;
    ship->fire_cooldown = 0;
    ship->fire_delay = FIRE_DELAY;
}

void update_ship(Ship* ship){
    if(IsKeyDown(KEY_A)){ //tourne le vaisseau vers la gauche
        ship->view_angle -= ship->rotation_speed;
    }
    if(IsKeyDown(KEY_D)){ //tourne le vaisseau vers la droite
        ship->view_angle+= ship->rotation_speed;
    }
    if(IsKeyDown(KEY_S)){ //ralentit la vitesse du vaisseau
        ship->speed_x *= ship->slow_down_ratio;
        ship->speed_y *= ship->slow_down_ratio;
    }
    if(IsKeyDown(KEY_W)){ //accélère le vaisseau selon la vitesse dans laquelle il regarde
        ship->speed_x += ship-> acceleration * cos(ship->view_angle * DEG2RAD);
        ship->speed_y += ship->acceleration * sin(ship->view_angle * DEG2RAD);
    }
    ship->coord_x += ship->speed_x;
    ship->coord_y += ship->speed_y;
    if((ship->coord_x - ship->radius) > SCREEN_WIDTH){ //sortie du vaisseau par la droite
        ship->coord_x = 0 - ship->radius;
    }
    if((ship->coord_x + ship->radius) < 0){ //sortie du vaisseau par la gauche
        ship->coord_x = SCREEN_WIDTH + ship->radius;
    }
    if((ship->coord_y - ship->radius) > SCREEN_HEIGHT){ //sortie du vaisseau par le bas
        ship->coord_y = 0 - ship->radius;
    }
    if((ship->coord_y + ship->radius) < 0){ //sortie du vaisseau par le haut
        ship->coord_y = SCREEN_HEIGHT + ship->radius;
    }
    if(ship->fire_cooldown > 0){
        ship->fire_cooldown--;
    }
}

void draw_ship(Ship ship){
    float a = ship.view_angle * DEG2RAD; //l'angle du nez en radians
    float spread = 140 * DEG2RAD; //l'écart des coins arrière
    Vector2 nose = {ship.coord_x + cos(a) * ship.radius,
                    ship.coord_y + sin(a) * ship.radius};
    Vector2 angle_left = {ship.coord_x + cos(a-spread) * ship.radius,
                          ship.coord_y + sin(a-spread) * ship.radius};
    Vector2 angle_right = {ship.coord_x + cos(a+spread) * ship.radius,
                           ship.coord_y + sin(a+spread) * ship.radius};
    DrawTriangleLines(nose, angle_left, angle_right, WHITE);
}
