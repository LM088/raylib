#include <iostream>
#include <raylib.h>

int player_score= 0; 
int cpu_score= 0; 

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

        if ( x + radius >= GetScreenWidth())
        {
            player_score++;
            ResetBall();
        }
        if (x - radius <= 0)
        {
             cpu_score++;
             ResetBall(); 
        }
    }

    void ResetBall()
    {
        x= GetScreenWidth()/2;
        y= GetScreenHeight()/2;

        int speed_choices[2]={1,-1};
        speed_x *= speed_choices[GetRandomValue(0,1)];

    }
};


class Paddle 
{

protected: // We did this just to avoid duplicate code. Everything in this class will just be inherited by the cpu class. 

    void LimitMovement()
    {
         if ( y + height >= GetScreenHeight())
        {
            y = (GetScreenHeight()-height) - 10 ;  
        }

        if (y  <= 0)
        {
            y = 10; 
        }
    }    

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

       LimitMovement();

    }
};

class CpuPaddle : public Paddle
{
public:
    void Update(int ball_y)
    {
        if(y+ height/2 > ball_y)
        {
            y -= speed; 
        }
        if(y+ height/2 < ball_y)
        {
            y +=speed; 
        } 
        LimitMovement(); 
    }
};

Ball ball; 
Paddle player;
CpuPaddle cpu;  

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

    cpu.width= 25;
    cpu.height= 120; 
    cpu.x= screen_width - 35; //-35 and not -10 because you have to take rectangle width into consideration. Rectangle is drawn from TOP LEFT corner.
    cpu.y= screen_height/2 - cpu.height/2; 
    cpu.speed= 6; 

    
    while(!WindowShouldClose())
    {
        BeginDrawing();

        // Updating position
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Checking for collision 
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{player.x,player.y,player.width,player.height}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y}, ball.radius, Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
        {
            ball.speed_x *= -1;
        }

        // clear background before drawing 
        ClearBackground(BLACK);
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        ball.Draw();
        player.Draw(); 
        cpu.Draw();
        DrawText(TextFormat("%i",player_score), screen_width/4, 20, 40, WHITE); 
        DrawText(TextFormat("%i",cpu_score), 3* screen_width/4, 20, 40, WHITE); 

        EndDrawing();
    }

    CloseWindow();
    return 0; 
}