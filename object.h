#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"
#include <iostream>
#include <fstream>
#include <time.h>
using std::string;
using std::fstream;

class Object{
    protected:
        int speed;
        int borderY;
        bool isCarLoaded = false;
        string car[10];

        coord pos;
        dimension size;

    public:
        Object();
        bool load(string car = "graphics/car.txt");
        void display();

        int getSpeed() { return speed; }
        void setBorder(int b) { borderY = b; }

        void updatePos(int playerSpeed);      // move based on player's speed
        coord getCoord() { return pos; }
        dimension getSize(){ return size; }

        bool isCollidingWith(Object car);

};

#endif