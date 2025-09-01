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
int offset= 75; 

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
    bool addSegment= false; 
    bool reset= false; 
    
    void Draw()
    {
        for (unsigned int i=0; i< body.size(); i++) // must declare i to be unsigned or else we're comparing 2 different data types.
        {
            float x= body[i].x;
            float y= body[i].y; 
            DrawRectangleRounded(Rectangle{offset + x*cellSize, offset + y*cellSize, (float)cellSize, (float)cellSize}, 0.5, 6, darkGreen);
        }
    }

    void Update()
    {
        body.push_front(Vector2Add(body[0], direction));
        if ( addSegment == true )
        {
            addSegment = false; 
        }else 
        {
            body.pop_back(); 
        }
    }

    void gameOver()
    {
        body={Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        direction= {1,0}; 
        reset= true; 
    }

    void CheckCollisionTail()
    {
        std::deque<Vector2> headlessBody= body;
        headlessBody.pop_front();
        for(unsigned int i= 0; i< headlessBody.size(); i++)
        {
            if(Vector2Equals(body[0], headlessBody[i]))
            {
                gameOver(); 
            }
        }


    }
};


class Food
{
public:
    Vector2 position; 
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody)
    {
        Image image= LoadImage("resources/apple.png");
        ImageResizeNN(&image, cellSize, cellSize);
        if (image.data == nullptr) 
        {
            std::cout << "Failed to load image! Check path or working directory.\n";
        }
        texture = LoadTextureFromImage(image); 
        UnloadImage(image);
        position= GenRandomPos(snakeBody); 
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        // Replacing DrawRectangle with DrawTexture
        //DrawRectangle(position.x*cellSize, position.y*cellSize, cellSize,cellSize, darkGreen);
        DrawTexture(texture, offset + position.x*cellSize, offset + position.y*cellSize, WHITE);
    }

    Vector2 GenRandomCell()
    {
        float x = GetRandomValue(0, cellCount-1);
        float y = GetRandomValue(0, cellCount-1);
        return Vector2{x,y}; 
    } 

    Vector2 GenRandomPos(std::deque<Vector2> snakeBody)
    {
        position= GenRandomCell(); 
        for ( unsigned int i= 0 ; i< snakeBody.size(); i++)
        {
            if( Vector2Equals(snakeBody[i], position))
            {
                position= GenRandomCell(); 
            }
        }
        return position; 
    }
};
 

int main()
{
    const int screen_width= cellSize*cellCount;
    const int screen_height= cellSize*cellCount; 
    
    InitWindow(2*offset+screen_width, 2*offset+screen_height, "SNAKE!");
    SetTargetFPS(60); 

    /*
    We're going to create a scope around the apple object. This is because: 
        - apple runs a destructor ~Food() to unload textures.
        - When we use CloseWindow(), all OpenGL textures are internally unloaded and the window context is destroyed.
        - This causes the destructor to run again and try to unload textures, but the memory has already been freed, causing a seg fault. 
        - Hence we wrap it in a scope so that the object is destroyed FIRST, then the window. 
    */
    
    {Snake snake;
     Food apple(snake.body);  

    while(!WindowShouldClose())
    {
        BeginDrawing();

        // Update
        if (eventTriggered(0.2) && !snake.reset)
        {
                snake.Update();
                snake.CheckCollisionTail(); 
        }
        
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
        {
            snake.direction= {0,1};
            snake.reset= false; 
        }
        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
        {
            snake.direction= {0,-1};
            snake.reset= false;
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
        {
            snake.direction= {-1,0};
            snake.reset= false;
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
        {
            snake.direction= {1,0};
            snake.reset= false;
        }
        

        // Draw
        ClearBackground(green);

        // this fun just draws the outline of a rect 
        // - we're basically trying to draw a frame around what *was* the viewport 
        // - frame by itself takes up 5 px, so you want to draw it in the space reserved for offset and not our viewport.
        // - offset is the space reserved as a frame around former viewport. 
        // - Hence start drawing rect 5 px away from where offset px end. 
        // - the width and height entered is the space inside the rectangular frame, which should be the same as our previously defined const screen_width and screen_height
        // - width and height entered also includes space taken up by the border, since rect outline is drawn from top left corner. 
        // - hence we add 5*2 px to both width and height
        // - All of these steps are important to ensure the former viweport area takes up exactly as much space as before, as the Snake and Food classes have also been constructed keeping these dimensions in mind. 
        DrawRectangleLinesEx(Rectangle{(float)offset-5, (float)offset-5, (float)screen_width+10, (float)screen_height+10}, 5, darkGreen);

        apple.Draw(); 
        snake.Draw(); 

        if (Vector2Equals(snake.body[0], apple.position ))
        {
            apple.position= apple.GenRandomPos(snake.body);
            snake.addSegment= true; 
        }

        if (snake.body[0].x == cellCount || snake.body[0].x == -1)
        {
            snake.gameOver(); 
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            snake.gameOver(); 
        }

        EndDrawing();
    }

    }

    CloseWindow();
}