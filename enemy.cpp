#include "enemy.h"

Enemy::Enemy(int b, int index){
    this->borderY = b;
    this->index = index;
    srand(time(NULL));
    speed = MIN_SPEED + rand()%(MAX_SPEED+1 - MIN_SPEED);
    pos.x = MIN_X + rand()%(MAX_X+1 - MIN_X);
    pos.y = 2 + rand()%(borderY-size.y);
    load();
}

void Enemy::updatePos(int playerSpeed){
    pos.x += (float)(speed - playerSpeed) / 20;
}