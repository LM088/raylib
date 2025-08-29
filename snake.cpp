#include <iostream>
#include <raylib.h>

int score=0; 
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

// Making grid 
int cellSize = 30;
int cellCount = 25;

// Making food class 
class Food
{
public:
    Vector2 position; 
    Texture2D texture;

    Food()
    {
        Image image= LoadImage("resources/apple.png");
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

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(green);
        apple.Draw(); 

        EndDrawing();
    }

    }

    CloseWindow();
}