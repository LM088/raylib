#include <iostream>
#include <raylib.h>
#include <deque>      // for body, better than array
#include <raymath.h>  // for Vector2Add fun 

/*

So far, our snake moves 60 blocks per sec.
Because we set fps to 60, the game loop runs 60 times per sec, and hence 
the update function also runs 60 times in a sec. 

Let's set it so that it doesn't update EVERY loop of the game loop. 
We'll set it so that it updates only after a certain amount of time has passed 
since the program has started execution. 

*/

int score=0; 
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

// Making grid 
int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currentTime= GetTime();
    if ( currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true; 
    }
    return false; 
}

class Snake 
{
public: 
    std::deque<Vector2> body={Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    Vector2 direction= {1,0}; 
    
    void Draw()
    {
        for (unsigned int i=0; i< body.size(); i++) // must declare i to be unsigned or else we're comparing 2 different data types.
        {
            float x= body[i].x;
            float y= body[i].y; 
            DrawRectangleRounded(Rectangle{x*cellSize, y*cellSize, (float)cellSize, (float)cellSize}, 0.5, 6, darkGreen);
        }
    }

    void Update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction)); 
    }
};


class Food
{
public:
    Vector2 position; 
    Texture2D texture;

    Food()
    {
        Image image= LoadImage("resources/apple.png");
        ImageResizeNN(&image, 100, 100);
        if (image.data == nullptr) 
        {
            std::cout << "Failed to load image! Check path or working directory.\n";
        }
        texture = LoadTextureFromImage(image); 
        UnloadImage(image);
        position= GenRandomPos(); 
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        // Replacing DrawRectangle with DrawTexture
        //DrawRectangle(position.x*cellSize, position.y*cellSize, cellSize,cellSize, darkGreen);
        DrawTexture(texture, position.x*cellSize, position.y*cellSize, WHITE);
    }

    Vector2 GenRandomPos()
    {
        float x = GetRandomValue(0, cellCount-1);
        float y = GetRandomValue(0, cellCount-1);
        return Vector2{x,y}; 
    } 
};
 

int main()
{
    const int screen_width= cellSize*cellCount;
    const int screen_height= cellSize*cellCount; 
    
    InitWindow(screen_width, screen_height, "SNAKE!");
    SetTargetFPS(60); 

    /*
    We're going to create a scope around the apple object. This is because: 
        - apple runs a destructor ~Food() to unload textures.
        - When we use CloseWindow(), all OpenGL textures are internally unloaded and the window context is destroyed.
        - This causes the destructor to run again and try to unload textures, but the memory has already been freed, causing a seg fault. 
        - Hence we wrap it in a scope so that the object is destroyed FIRST, then the window. 
    */
    
    {Food apple; 
     Snake snake; 

    while(!WindowShouldClose())
    {
        BeginDrawing();

        // Update
        if (eventTriggered(0.2))
        {
            snake.Update();
        }
        

        // Draw
        ClearBackground(green);
        apple.Draw(); 
        snake.Draw(); 

        EndDrawing();
    }

    }

    CloseWindow();
}