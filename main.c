#include "raylib.h"
#include "config.h"
#include "ship.h"
int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
    SetTargetFPS(60);
    Ship ship;
    init_ship(&ship);
    while(!WindowShouldClose()){
        update_ship(&ship);
        BeginDrawing();
        ClearBackground(BLACK);
        draw_ship(ship);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
