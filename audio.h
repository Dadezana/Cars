#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include "utils.h"
#include "car.h"

class Audio{
    sf::Sound firstGear;                // 0 - 35 Km/h
    sf::Sound secondGear;               // 35 - 75 Km/h
    sf::Sound thirdGear;                // 75 - 165 Km/h
    sf::Sound fourthGear;               // 165 - 200 Km/h
    sf::Sound brake;
    sf::Sound sameSpeed;
    sf::Sound horn;
    sf::Sound crash;
    sf::Sound stop;
    sf::Music bgMusic;

    sf::SoundBuffer firstGearBuffer;    
    sf::SoundBuffer secondGearBuffer;
    sf::SoundBuffer thirdGearBuffer;
    sf::SoundBuffer fourthGearBuffer;
    sf::SoundBuffer brakeBuffer;
    sf::SoundBuffer sameSpeedBuffer;
    sf::SoundBuffer hornBuffer;
    sf::SoundBuffer crashBuffer;
    sf::SoundBuffer stopBuffer;

    bool audioGearPlaying();

    public:
        Audio();
        void playAccelerate(int speed);
        void playBrake(int speed);
        void playSame(int speed);
        void  stopAllSounds(bool justGears = false);
        void setVolume(int vol = 100);
        void playHorn();
        void playCrash();
};

#endif