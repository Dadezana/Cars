#include "audio.h"

Audio::Audio(){
    firstGearBuffer.loadFromFile("sounds/firstGear.wav");
    secondGearBuffer.loadFromFile("sounds/secondGear.wav");
    thirdGearBuffer.loadFromFile("sounds/thirdGear.wav");
    fourthGearBuffer.loadFromFile("sounds/fourthGear.wav");
    brakeBuffer.loadFromFile("sounds/brake.wav");
    sameSpeedBuffer.loadFromFile("sounds/sameSpeed.wav");
    hornBuffer.loadFromFile("sounds/horn.wav");
    crashBuffer.loadFromFile("sounds/crash.wav");
    stopBuffer.loadFromFile("sounds/stop.wav");
    bgMusic.openFromFile("sounds/music.wav");
    bgMusic.setLoop(true);
    bgMusic.play();

    firstGear.setBuffer(firstGearBuffer);
    secondGear.setBuffer(secondGearBuffer);
    thirdGear.setBuffer(thirdGearBuffer);
    fourthGear.setBuffer(fourthGearBuffer);
    brake.setBuffer(brakeBuffer);
    sameSpeed.setBuffer(sameSpeedBuffer);
    sameSpeed.setLoop(true);
    crash.setBuffer(crashBuffer);
    horn.setBuffer(hornBuffer);
    stop.setBuffer(stopBuffer);
    stop.setLoop(true);

    setVolume(60);
}

void Audio::playAccelerate(int speed){


    if(speed >= 198){
        stopAllSounds(true);
        playSame(speed);
        return;
    }

    if(!audioGearPlaying() && speed > FOURTH_GEAR_MIN_SPEED){
        if(fourthGear.getStatus() == sf::SoundSource::Stopped){
            stopAllSounds();
            fourthGear.play();
        }

    }else if(!audioGearPlaying() && speed > THIRD_GEAR_MIN_SPEED){
        if(thirdGear.getStatus() == sf::SoundSource::Stopped){
            stopAllSounds();
            thirdGear.play();
        }

    }else if(!audioGearPlaying() && speed > SECOND_GEAR_MIN_SPEED){
        if(secondGear.getStatus() == sf::SoundSource::Stopped){
            stopAllSounds();
            secondGear.play();
        }

    }else if(!audioGearPlaying() && speed > FIRST_GEAR_MIN_SPEED){
        if(firstGear.getStatus() == sf::SoundSource::Stopped){
            stopAllSounds();
            firstGear.play();
        }
    }
}

void Audio::playBrake(int speed){
    if(speed == 0){
        brake.stop();
        return;
    }
    
    if(brake.getStatus() == sf::SoundSource::Stopped){
        stopAllSounds();
        brake.play();
    }
}

void Audio::playSame(int speed){
    if(speed == 0){
        sameSpeed.stop();
        if(stop.getStatus() == sf::SoundSource::Stopped) stop.play();
        return;
    }
    if(sameSpeed.getStatus() == sf::SoundSource::Stopped){
        stopAllSounds();
        sameSpeed.play();
    }
        
}

void Audio::playHorn(){
    if(horn.getStatus() != sf::SoundSource::Playing){
        horn.play();
    }
}

void Audio::playCrash(){
    if(crash.getStatus() != sf::SoundSource::Playing){
        stopAllSounds();
        crash.play();
    }
}

bool Audio::audioGearPlaying(){

    return (
        fourthGear.getStatus() == sf::SoundSource::Playing ||
        thirdGear.getStatus() == sf::SoundSource::Playing ||
        secondGear.getStatus() == sf::SoundSource::Playing ||
        firstGear.getStatus() == sf::SoundSource::Playing
    );

}

void Audio::stopAllSounds(bool justGears){

    if(justGears){
        firstGear.stop();
        secondGear.stop();
        thirdGear.stop();
        fourthGear.stop();
        return;
    }
    firstGear.stop();
    secondGear.stop();
    thirdGear.stop();
    fourthGear.stop();
    brake.stop();
    sameSpeed.stop();
    stop.stop();
}

void Audio::setVolume(int vol){
    if(vol > 100) vol = 100;
    firstGear.setVolume(vol-15);
    secondGear.setVolume(vol-15 > 0 ? vol-15 : vol);
    thirdGear.setVolume(vol-15 > 0 ? vol-15 : vol);
    fourthGear.setVolume(vol-15 > 0 ? vol-15 : vol);
    brake.setVolume(vol-15 > 0 ? vol-15 : vol);
    sameSpeed.setVolume(vol-15 > 0 ? vol-15 : vol);
    crash.setVolume(vol);
    horn.setVolume(vol);
    stop.setVolume(vol * 2 <= 100 ? vol*2 : 100);
    bgMusic.setVolume(vol * 2 <= 100 ? vol*2 : 100);
}