#include "raylib.h"
#include "config.h"
#include "ship.h"
#include "asteroid.h"
#include "missiles.h"
#include "collisions.h"
#include <raymath.h>
#include "game.h"
const int score_table[3] = {1, 2, 3};
int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
    InitAudioDevice();
    Sound laser = LoadSound("laserShoot.wav");
    Sound thrust = LoadSound("thrusterFire_000.ogg");
    SetTargetFPS(60);
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    float shake = 0;
    Ship ship;
    Asteroid asteroid[MAX_ASTEROIDS];
    Missile missiles[MAX_MISSILE];
    init_ship(&ship);
    State state = STATE_TITLE;
    int score = 0;
    for(int i = 0; i<MAX_ASTEROIDS; i++){ //initialisation du tableau d'asteroid à alive false
        asteroid[i].alive = false;
    }
    for(int i = 0; i<MAX_MISSILE; i++){ //initialise les missiles alive à false
        missiles[i].alive = false;
    }
    while(!WindowShouldClose()){
        switch (state){
            case STATE_TITLE: // ecran d'accueil
                BeginDrawing();
                int title_text_lengh = MeasureText(TextFormat("Pour commencer la partie, appuyez sur Entree"), 20);
                DrawText(TextFormat("Pour commencer la partie, appuyez sur Entree"), (SCREEN_WIDTH/2)- (title_text_lengh/2), (SCREEN_HEIGHT/2)-10, 20, WHITE);
                EndDrawing();
                if(IsKeyDown(KEY_ENTER)){
                    reset_game(&ship, missiles, asteroid, &score);
                    state = STATE_PLAYING;
                }
                break;
            case STATE_PLAYING: //partie en cours
                update_ship(&ship, thrust);
                if(IsKeyDown(KEY_SPACE) && ship.fire_cooldown <= 0){ //tirs
                   for(int i = 0; i<MAX_MISSILE; i++){
                        if(!missiles[i].alive){
                            init_missile(&missiles[i], ship);
                            SetSoundPitch(laser, GetRandomValue(90, 110) /100.0f);
                            PlaySound(laser);
                            ship.flash_timer = FLASH_DURATION;
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
                for(int i = 0; i < MAX_MISSILE; i++){
                    if(missiles[i].alive){
                        for(int j = 0; j < MAX_ASTEROIDS; j++){
                            if(asteroid[j].alive){
                                if(circles_collide(missiles[i].coord_x, missiles[i].coord_y, missiles[i].radius, asteroid[j].coord_x, asteroid[j].coord_y, asteroid[j].radius)){
                                    float last_x = asteroid[j].coord_x;
                                    float last_y = asteroid[j].coord_y;
                                    AsteroidSize last_size = asteroid[j].size;
                                    shake = SHAKE_STRENGTH;
                                    score += score_table[last_size];
                                    missiles[i].alive = false;
                                    asteroid[j].alive = false;
                                    int created = 0;
                                    if(last_size != SMALL){
                                        for(int k = 0; created < 2 && k < MAX_ASTEROIDS; k++){
                                            if(asteroid[k].alive == false){
                                                init_asteroid(&asteroid[k], last_x, last_y, last_size +1);
                                                created++;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
                for(int i = 0; i < MAX_ASTEROIDS; i++){
                    if(ship.invincible_timer == 0 && asteroid[i].alive && circles_collide(ship.coord_x, ship.coord_y, ship.radius, asteroid[i].coord_x, asteroid[i].coord_y, asteroid[i].radius)){
                        ship.lives--;
                        ship.speed_x = 0;
                        ship.speed_y = 0;
                        ship.invincible_timer = INVINCIBLE_DURATION;
                        shake = SHAKE_STRENGTH;
                        if(ship.lives == 0){
                            state = STATE_GAME_OVER;
                        }
                        break;
                    }
                }
                camera.offset.x = (GetRandomValue(-100, 100) / 100.0f) * shake;
                camera.offset.y = (GetRandomValue(-100, 100) / 100.0f) * shake;
                shake *= 0.9;
                if(shake < 0.1){
                    shake = 0;
                }
                BeginDrawing();
                BeginMode2D(camera);
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
                EndMode2D();
                DrawText(TextFormat("Vitesse : %.2f", sqrt(ship.speed_x * ship.speed_x + ship.speed_y * ship.speed_y)), 10, 10, 20, WHITE);
                DrawText(TextFormat("Vies : %d", ship.lives), 10, 30, 20, WHITE);
                DrawText(TextFormat("Score : %d", score), 10, 50, 20, WHITE);
                EndDrawing();
                        break;
                    case STATE_GAME_OVER:
                        int end_text_lengh_3 = MeasureText(TextFormat("Pour recommencer, appuyez sur Entree"), 20);
                        BeginDrawing();
                        ClearBackground(BLACK);
                        DrawText(TextFormat("Perdu !"), (SCREEN_WIDTH/2)- (end_text_lengh_3/2), (SCREEN_HEIGHT/2)-10, 20, WHITE);
                        DrawText(TextFormat("Score : %d", score), (SCREEN_WIDTH/2)- (end_text_lengh_3/2), (SCREEN_HEIGHT/2)+10, 20, WHITE);
                        DrawText(TextFormat("Pour recommencer, appuyez sur Entree"), (SCREEN_WIDTH/2)- (end_text_lengh_3/2), (SCREEN_HEIGHT/2)+30, 20, WHITE);
                        EndDrawing();
                        if(IsKeyDown(KEY_ENTER)){
                            reset_game(&ship, missiles, asteroid, &score);
                            state = STATE_PLAYING;
                        }
                }

            }


    UnloadSound(thrust);
    UnloadSound(laser);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
