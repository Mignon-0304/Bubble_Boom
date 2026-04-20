#include "raylib.h"
#include <iostream>
#include "Bubble.h"
#include "Player.h"
#include "Make_Font.h"
#include <string>
using namespace std;


int main() {

    int WINDOW_HEIGHT=450;
    int WINDOW_WIDTH=800;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OMG first Raylib with zero ideas!");
    SetTargetFPS(60);
    SetRandomSeed(time(NULL));

    bool beginning=true;
    Bubble bubbles[5];

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    const char msg[50] = "Click the bubbles to get points!";

    Vector2 msg_position = { 40, 40 };
    int msg_size = 40;
    Font fontDefault = makefont("resources/Impact.ttf", msg_size);
    Vector2 num_position = { 40, 200 };
    int num_size = 30;
    Font number = makefont("resources/RepriseTitleStd.ttf", msg_size);
    Shader sdfShader = LoadShader(0, "resources/sdf.fs");

    Player player;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if(beginning){
            for(int i=0;i<5;i++){
                int x = rand() % (WINDOW_WIDTH-39) + 20;
                int y = rand() % (WINDOW_HEIGHT-39) + 20;
                Bubble temp(static_cast<float>(x), static_cast<float>(y));
                bubbles[i] = temp;
            }
            beginning = false;
        }
        if(Bubble::restart()){
            for(int i=0;i<5;i++) bubbles[i].turnLife(REBORN);
        }
        for(int i=0;i<5;i++){
            if(bubbles[i].getLife()){
                DrawCircleV(bubbles[i].getCenter(), 20.0, BLUE);
            }
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mouse_vec = GetMousePosition();
            for(int i=0;i<5;i++){
                if(!bubbles[i].getLife()) continue;
                if(CheckCollisionPointCircle(mouse_vec, bubbles[i].getCenter(), 20.0)){
                    bubbles[i].turnLife(KILL);
                    player.addScore();
                    int x = rand() % (WINDOW_WIDTH-39) + 20;
                    int y = rand() % (WINDOW_HEIGHT-39) + 20;
                    bubbles[i].setCenter(static_cast<float>(x), static_cast<float>(y));
                }
            }
        }
        BeginShaderMode(sdfShader);
            DrawTextEx(fontDefault, msg, msg_position, msg_size, 0, BLACK);
        EndShaderMode();


        char Score[50];
        snprintf(Score, 50, "Point: %d", player.getScore());
        BeginShaderMode(sdfShader);
            DrawTextEx(number, Score, num_position, num_size, 0, BLACK);
        EndShaderMode();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
