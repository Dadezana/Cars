#include "car.h"

Car::Car(int speed){
    this->speed = 0;
    maxSpeed = speed < 200 ? speed : 200;
    pos.y = 2;
    pos.x = 30;
    gear = 1;
    load();
}

void Car::brake(){
    if(speed <= 0){
        speed = 0;
        return;
    }        	
    speed -= 2;
}

void Car::accelerate(){
    if (speed+1 <= maxSpeed)
        speed += 1;
}

void Car::turn(bool right){
    
    if(right){ 
        if(pos.y + size.y < borderY-1)
            pos.y++;
    }
    else if(pos.y > 2) pos.y--;
}

int Car::getMaxSpeed(){
    return maxSpeed;
}
