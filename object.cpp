#include "object.h"

Object::Object(){

}

bool Object::load(string car){
    fstream c(car);
    if (!c.is_open()){
        return false;
    }

    string line;
    int i = 0;
    while(std::getline(c, line)){
        this->car[i] = line;
        i++;
    }
    size.y = i-2;
    isCarLoaded = true;
    return true;
}

void Object::display(){
    if(!isCarLoaded) return;
    for(int i = 0; i < 10; i++)
    {
        gotoxy(pos.x, pos.y+i);
        cout << car[i];
    }
}

// bool Object::isCollidingWith(coord c, dimension s){
//     return(
//         ( (pos.x <= c.x + s.x && pos.x >= c.x) || (pos.x + size.x <= c.x + s.x && pos.x + size.x >= c.x) ) &&
//         ( (pos.y <= c.y + s.y && pos.y >= c.y) || (pos.y + size.y <= c.y + s.y && pos.y + size.y >= c.y) )
//     );
// }

bool Object::isCollidingWith(Object car){
    coord c = car.getCoord();
    dimension s = car.getSize();
    return(
        ( (pos.x <= c.x + s.x && pos.x >= c.x) || (pos.x + size.x <= c.x + s.x && pos.x + size.x >= c.x) ) &&
        ( (pos.y <= c.y + s.y && pos.y >= c.y) || (pos.y + size.y <= c.y + s.y && pos.y + size.y >= c.y) )
    );
}