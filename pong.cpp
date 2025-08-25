#include <iostream>
#include <raylib.h>

int main()
{
    std::cout << "Starting game ..." << "\n";
    const int screen_width = 1280;
    const int screen_height = 800; 
    InitWindow(screen_width, screen_height, "Pong!");
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        DrawCircle(screen_width/2, screen_height/2, 20, WHITE);
        DrawRectangle(10, screen_height/2 - 60, 25, 120, WHITE);
        // -35 and not -10 because you have to take rectangle width into consideration. 
        // rectangle is drawn from TOP LEFT corner 
        DrawRectangle(screen_width-35, screen_height/2-60, 25, 120, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0; 
}