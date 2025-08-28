#include <iostream>
#include <raylib.h>

int score=0; 
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int main()
{
    const int screen_width= 750;
    const int screen_height= 750; 
    
    InitWindow(screen_width, screen_height, "SNAKE!");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }
    CloseWindow();
}