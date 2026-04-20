#include "Player.h"

void Player::addScore(){
    score+=20;
}

int Player::getScore(){
    return score;
}

int Player::getLives(){return lives;}

void Player::lessLives(){
    lives--;
}