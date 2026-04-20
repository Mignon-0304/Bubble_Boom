#ifndef BUBBLE_H
#define BUBBLE_H


#include "raylib.h"

class Bubble{
    float centerX;
    float centerY;
    bool life = true;
    public:
    void turnLife();
    bool getLife();
    Bubble(float x=20.0, float y=20.0){centerX = x; centerY = y;}
    Vector2 getCenter();
};

#endif