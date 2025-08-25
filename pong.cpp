#include <iostream>
#include <raylib.h>

int main()
{
    std::cout << "Starting game ..." << "\n";
    const int screen_width = 1280;
    const int screen_height = 800; 
    InitWindow(screen_width, screen_height, "Pong!");
    SetTargetFPS(60);
    
    while(!WindowShouldClose)
    {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
    return 0; 
}