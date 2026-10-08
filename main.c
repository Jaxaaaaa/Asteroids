#include "raylib.h"
#include "config.h"
#include "ship.h"
#include "asteroid.h"
#include "missiles.h"
int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
    SetTargetFPS(60);
    Ship ship;
    Asteroid asteroid[MAX_ASTEROIDS];
    Missile missiles[MAX_MISSILE];
    init_ship(&ship);
    for(int i = 0; i<MAX_ASTEROIDS; i++){ //initialisation du tableau d'asteroid à alive false
        asteroid[i].alive = false;
    }
    for(int i = 0; i< 5; i++){
        init_asteroid(&asteroid[i], GetRandomValue(0,SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT), 40);
    }
    for(int i = 0; i<MAX_MISSILE; i++){ //initialise les missiles alive à false
        missiles[i].alive = false;
    }
    while(!WindowShouldClose()){
        update_ship(&ship);
        if(IsKeyDown(KEY_SPACE) && ship.fire_cooldown <= 0){
           for(int i = 0; i<MAX_MISSILE; i++){
                if(!missiles[i].alive){
                    init_missile(&missiles[i], ship);
                    ship.fire_cooldown = ship.fire_delay; //reset le cooldown des tirs après un tir
                    break;
                }
           }
        }
        for(int i = 0; i < MAX_ASTEROIDS; i++){ //update les astéroides encore présents
            if(asteroid[i].alive == true){
                update_asteroid(&asteroid[i]);
            }
        }
        for(int i = 0; i < MAX_MISSILE; i++){ //update les missiles encore présents
            if(missiles[i].alive){
                update_missile(&missiles[i]);
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for(int i = 0; i < MAX_ASTEROIDS; i++){
            if(asteroid[i].alive == true){
                draw_asteroid(asteroid[i]);
            }
        }
        for(int i = 0; i < MAX_MISSILE; i++){
            if(missiles[i].alive){
                draw_missile(missiles[i]);
            }
        }
        draw_ship(ship);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
