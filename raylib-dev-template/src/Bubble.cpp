#include "raylib.h"
#include "Bubble.h"

void Bubble::turnLife(){life=!life;}
Vector2 Bubble::getCenter(){
    return Vector2{centerX, centerY};
}
bool Bubble::getLife(){return life;}