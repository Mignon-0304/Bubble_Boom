#include "raylib.h"
#include "Bubble.h"

void Bubble::turnLife(bubble_do d){
    life=!life;
    if(d==KILL) survivor--;
    else survivor++;
}
Vector2 Bubble::getCenter(){
    return Vector2{centerX, centerY};
}
bool Bubble::getLife(){return life;}

void Bubble::setCenter(float x, float y){
    centerX = x;
    centerY = y;
}

bool Bubble::restart(){
    return (survivor == 0);
}

int Bubble::survivor = 5;