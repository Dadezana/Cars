#ifndef ENEMY_H
#define ENEMY_H

#include "object.h"

class Enemy : public Object{
    
    const static int MAX_SPEED = 100;
    const static int MIN_SPEED = 50;
    const static int MIN_X = 190;
    const static int MAX_X = 300;
    int index;
    public:
        Enemy(int b, int index);

        void updatePos(int playerSpeed);      // move based on player's speed
        int getIndex(){ return index; }

        bool operator==(const int &en){
            return index == en;
        }
};
#endif