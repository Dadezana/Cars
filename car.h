#ifndef CAR_H
#define CAR_H

#define FIRST_GEAR_MIN_SPEED 0
#define SECOND_GEAR_MIN_SPEED 35
#define THIRD_GEAR_MIN_SPEED 75
#define FOURTH_GEAR_MIN_SPEED 160

#include "object.h"

class Car : public Object{

    private: 
        int maxSpeed;
        int gear;

    public:
        Car(int speed = 200);
        
        int getMaxSpeed();
        int getGear() { return gear; }

        void accelerate();
        void brake();
        void turn(bool right);

        
};

#endif