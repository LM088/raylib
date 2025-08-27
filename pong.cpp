#include <iostream>
#include <raylib.h>

class Ball 
{
public:
    float x,y = 0;
    int speed_x, speed_y = 0; 
    int radius= 0; 

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update()
    {
        x += speed_x; 
        y += speed_y; 

        if ( y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1; 
        }

        if ( x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x *= -1; 
        }
    }
};


class Paddle 
{
public:
    float x,y = 0;
    float width, height = 0;    
    int speed= 0; 

    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update()
    {

        if (IsKeyDown(KEY_UP))
        {
            y -= speed; 
        }

        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }

        if ( y + height >= GetScreenHeight())
        {
            y = (GetScreenHeight()-height) - 10 ;  
        }

        if (y  <= 0)
        {
            y = 10; 
        }
    }
};

Ball ball; 
Paddle player; 

int main()
{
    std::cout << "Starting game ..." << "\n";
    const int screen_width = 1280;
    const int screen_height = 800; 
    InitWindow(screen_width, screen_height, "Pong!");
    SetTargetFPS(60);


    ball.x= screen_width/2;
    ball.y= screen_height/2;
    ball.radius= 20;
    ball.speed_x= 7;
    ball.speed_y= 7;

    player.width= 25;
    player.height= 120;
    player.x= 10; 
    player.y= screen_height/2 - player.height/2;
    player.speed= 6;

    
    while(!WindowShouldClose())
    {
        BeginDrawing();

        // Updating position
        ball.Update();
        player.Update();

        // clear background before drawing 
        ClearBackground(BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        ball.Draw();
        player.Draw();
        // -35 and not -10 because you have to take rectangle width into consideration. 
        // rectangle is drawn from TOP LEFT corner 
        DrawRectangle(screen_width-35, screen_height/2-60, 25, 120, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0; 
}