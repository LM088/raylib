#include <raylib.h>

int main()
{
    int ballX= 400; 
    int ballY= 400; 
    Color pink= {207, 101, 150, 225};
    InitWindow(800,800,"Game");
    SetTargetFPS(60);

    //Game loop
    while(!WindowShouldClose())
    {
        // 1. Event Handling
        if (IsKeyDown(KEY_RIGHT))
        {
            ballX += 3;
        }else if (IsKeyDown(KEY_LEFT))
        {
            ballX -= 3;
        }else if (IsKeyDown(KEY_UP))
        {
            ballY -= 3;
        }else if (IsKeyDown(KEY_DOWN))
        {
            ballY += 3;
        }
        // 2. Updating Positions 
    
        // 3. Drawing
        ClearBackground(pink); 
        BeginDrawing();
        DrawCircle(ballX,ballY,20,WHITE);

        EndDrawing();
        
    }; 

    CloseWindow();
    return 0;
}