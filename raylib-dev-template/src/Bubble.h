#ifndef BUBBLE_H
#define BUBBLE_H


#include "raylib.h"

enum bubble_do {KILL, REBORN};

class Bubble{
    float centerX;
    float centerY;
    bool life = true;
    static int survivor;
    public:
    void turnLife(bubble_do);
    bool getLife();
    Bubble(float x=20.0, float y=20.0){centerX = x; centerY = y;}
    Vector2 getCenter();
    void setCenter(float x, float y);
    static bool restart();
};

#endif