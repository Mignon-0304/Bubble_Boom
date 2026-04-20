#include "raylib.h"
#include <iostream>
#include "Bubble.h"
#include "Player.h"
#include "Make_Font.h"
#include <string>
#include <vector>
using namespace std;
#define WINDOW_HEIGHT 450
#define WINDOW_WIDTH 800

int score_thshld = 100;
void harder();
vector<Bubble> bubbles;

enum Game_state {ALIVE, DEAD};

int main() {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "First Raylib HORRIFYING");
    SetTargetFPS(60);
    SetRandomSeed(time(NULL));

    int frames = 0;
    int timeLeft = 6;

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    const char msg[50] = "Click the bubbles to get points!";

    int msg_size = 40;
    Font fontDefault = makefont("resources/Impact.ttf", msg_size);
    Vector2 msg_position = { 40, 40 };
    Vector2 end_position = {100, 100};
    Vector2 fscore_position = {100, 300};


    int num_size = 30;
    Font number = makefont("resources/RepriseTitleStd.ttf", num_size);
    Vector2 num_position = { 40, 200 };
    Vector2 time_position = {40, 300};
    Vector2 life_position = {40, 400};

    Shader sdfShader = LoadShader(0, "resources/sdf.fs");

    Player player;
    Game_state state = ALIVE;

    for(int i=0;i<5;i++){
        int x = GetRandomValue(20, WINDOW_WIDTH-20);
        int y = GetRandomValue(20, WINDOW_HEIGHT-20);
        Bubble temp(static_cast<float>(x), static_cast<float>(y));
        bubbles.push_back(temp);
    }

    while (!WindowShouldClose()) {

        switch(state){
        case ALIVE:
        frames++;
        if(frames%60==0 && timeLeft>0){
            timeLeft--;
            if(timeLeft==0) player.lessLives();
            frames = 0;
        }

        if(Bubble::restart() && player.getLives()!=0){
            for(int i=0;i<bubbles.size();i++) bubbles[i].turnLife(REBORN);
            if(timeLeft!=0) player.addScore();
            timeLeft = 6;
            if(player.getScore()==score_thshld) harder();
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Vector2 mouse_vec = GetMousePosition();
            for(int i=0;i<bubbles.size();i++){
                if(!bubbles[i].getLife()) continue;
                if(CheckCollisionPointCircle(mouse_vec, bubbles[i].getCenter(), 20.0)){
                    bubbles[i].turnLife(KILL);
                    int x = GetRandomValue(20, WINDOW_WIDTH-20);
                    int y = GetRandomValue(20, WINDOW_HEIGHT-20);
                    bubbles[i].setCenter(static_cast<float>(x), static_cast<float>(y));
                }
            }
        }
        if(player.getLives()==0 && frames==59){
            /*end of game idk I'll do it later*/
            state = DEAD;
        }
        break;

        case DEAD:
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(state){
        case ALIVE: {
        
        for(int i=0;i<bubbles.size();i++){
            if(bubbles[i].getLife()){
                DrawCircleV(bubbles[i].getCenter(), 20.0, BLUE);
            }
        }
        
        char Score[50];
        snprintf(Score, 50, "Point: %d", player.getScore());
        char Time[50];
        snprintf(Time, 50, "Timer: %d", timeLeft);
        string lives;
        if(player.getLives()==3) lives = "Lives: -0-0-0-";
        else if(player.getLives()==2) lives = "Lives: -0-0-#-";
        else if(player.getLives()==1) lives = "Lives: -0-#-#-";
        else lives = "Lives: -#-#-#";
        BeginShaderMode(sdfShader);
            DrawTextEx(fontDefault, msg, msg_position, msg_size, 0, BLACK);
            DrawTextEx(number, Score, num_position, num_size, 0, ORANGE);
            if(timeLeft!=0) DrawTextEx(number, Time, time_position, num_size, 0, ORANGE);
            else DrawTextEx(number, Time, time_position, num_size, 0, MAROON);
            DrawTextEx(number, &lives[0], life_position, num_size, 0, RED);
        EndShaderMode();
        break;
        }

        case DEAD:{
        BeginShaderMode(sdfShader);
        DrawTextEx(fontDefault, "You're Dead.\nLife is hard.\nAnyway,\nThanks for playing!", 
        end_position, msg_size, 0, BLACK);
        char FinalScore[50];
        snprintf(FinalScore, 50, "Final Score: %d", player.getScore());
        DrawTextEx(number, FinalScore, fscore_position, num_size, 0, BROWN);
        EndShaderMode();
        break;
        }

    }
        EndDrawing();
    }

    UnloadFont(fontDefault);
    UnloadFont(number);
    UnloadShader(sdfShader);

    CloseWindow();
    return 0;
}

void harder(){
    score_thshld*=2;
    for(int i=0;i<3;i++){
        int x = GetRandomValue(20, WINDOW_WIDTH-20);
        int y = GetRandomValue(20, WINDOW_HEIGHT-20);
        bubbles.push_back(Bubble{static_cast<float>(x), static_cast<float>(y)});
    }
    Bubble::survivor = bubbles.size();
}
