#include <raylib.h>

int main()
{
    InitWindow(800,800,"Game");
    SetTargetFPS(60);

    //Game loop
    while(!WindowShouldClose())
    {
        // 1. Event Handling 
        // 2. Updating Positions 
        // 3. Drawing 
        BeginDrawing();
        EndDrawing();
        
    }; 

    CloseWindow();
    return 0;
}