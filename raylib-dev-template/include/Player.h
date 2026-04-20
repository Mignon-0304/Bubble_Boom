#ifndef PLAYER_H
#define PLAYER_H

class Player{
    int score=0;
    int lives=3;
    public:
    void addScore();
    int getScore();
    int getLives();
    void lessLives();
};

#endif