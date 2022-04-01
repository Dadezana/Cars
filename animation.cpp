#include "animation.h"
#include "utils.h"

Animation::Animation(){
    lenght = strisce.length();
    frame = 0;
    load();
}

void Animation::load(string world){			
    fstream map(world);
    
    if (!map.is_open()){
        cout << RED << "No map found" << RESET;
        return;
    }
    string line;
    weight = 0;

    while(getline(map, line)){
        camp[weight] = line;
        weight += 1;
    }
    borderY = weight-1;
}

void Animation::display(int speed){
    gotoxy(0, 0);
    for (int i = 0; i < weight; i++){
        if (i != 12 && i != 24)
            cout << ' ' << camp[i] << "\n";
        else{
            if(i == borderY){ cout << camp[i]; continue;}
            cout << ' ';
            for (int j = frame; j < lenght-4; j++)
                cout << strisce[j];
            if (frame != 0)
                for (int j = 0; j < frame; j++)
                    cout << strisce[j];
            
            for (int j = lenght-4; j < lenght-1; j++)
                cout << ' '; //sleep
        }
    }
    
    if(speed > 0)
        if (frame < lenght-1) frame++;
        else frame = 0;
}