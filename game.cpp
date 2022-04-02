#include <iostream>
#include <string>
#include <list>
#include <time.h>
#include <chrono>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "car.h"
#include "animation.h"
#include "enemy.h"
#include "menu.h"
#include "audio.h"
#define RIGHT true
#define LEFT false
#define MAX_SPAWN_TIME 8	// if no enemy spawns within 8sec, a new one will spawn immediatly
using namespace std;

bool canSpawn(){
	srand(time(NULL));
	static auto spawnStart = chrono::system_clock::now();
	static auto spawnEnd = chrono::system_clock::now();
	spawnEnd = chrono::system_clock::now();
	chrono::duration<double> secs = spawnEnd - spawnStart;
	static int max = 50;

	if( secs.count() > 1 ){
		max += 1;
		spawnStart = chrono::system_clock::now();
	}
	if( (rand()%max) % 20 == 0) return true;

	return false;
}

void gameOver(){
	cout << BOLDRED;
	gotoxy(77, 10);
	cout << "███▀▀▀██ ███▀▀▀███ ███▀█▄█▀███ ██▀▀▀    ███▀▀▀███ ▀███ ███▀ ██▀▀▀ ██▀▀▀▀██▄";
	gotoxy(77, 11); 
	cout << "██    ██ ██     ██ ██   █   ██ ██       ██     ██   ██ ██   ██    ██     ██";
	gotoxy(77, 12); 
	cout << "██   ▄▄▄ ██▄▄▄▄▄██ ██   ▀   ██ ██▀▀▀    ██     ██   ██ ██   ██▀▀▀ ██▄▄▄▄▄▀▀";
	gotoxy(77, 13); 
	cout << "██    ██ ██     ██ ██       ██ ██       ██     ██   ██ ██   ██    ██     ██";
	gotoxy(77, 14); 
	cout << "███▄▄▄██ ██     ██ ██       ██ ██▄▄▄    ███▄▄▄███    ▀█▀    ██▄▄▄ ██     ██▄";
	cout << RESET;
}

int main(){

	bool canPlayAudio = true;
	const int MAX_SPEED_ALLOWED = 200;
	system("clear");
/**
 * MAIN MENU
*/

	const int NUM_OPTIONS = 5;
	char options[NUM_OPTIONS][CHAR_OPZIONE_MAX];
	strcpy(options[0], "Play");
	strcpy(options[1], "Audio: Yes");
	strcpy(options[2], "Quit");
	strcpy(options[3], "Opzione 4");
	strcpy(options[4], "Opzione 5");
	Menu a(0, options, NUM_OPTIONS);

	auto audioStart = chrono::system_clock::now();
	auto audioEnd = chrono::system_clock::now();
	chrono::duration<double> audioSec;

	while(true){
		int chose = a.intefacciaRisultato();
		audioEnd = chrono::system_clock::now();
		audioSec = audioEnd - audioStart;

		if(chose == 0) break;
		else if(chose == 1 && audioSec.count() > 0.3){
			canPlayAudio = !canPlayAudio;
			a.setAudio(canPlayAudio, 1);
			audioStart = chrono::system_clock::now();
		}else if(chose == 2){
			exit(0);
		}	
	}
	

/**
 * SETTING UP THE GAME
*/
	Animation map;
	Car car;
	car.setBorder(map.getBorder());

	int index = 0;
	list<Enemy> enemies;	// other cars spawning
	list<int> indexes;		// keep track of car inside the list

	map.display(car.getSpeed());
	car.display();

// car controls
	bool isAccelerating = false;
	bool isBraking = false;
	bool isLeft = false;
	bool isRight = false;
	auto carStart = chrono::system_clock::now();
	auto carEnd = chrono::system_clock::now();
	chrono::duration<double> seconds;

	char c;
	
// to update cars's positions
	bool canUpdate;
	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();

// to spawn a new enemy
	auto timerStart = chrono::system_clock::now();
	auto timerEnd = chrono::system_clock::now();
	chrono::duration<float> timeLastSpawn;				// last time an enemy spawned

// deleting an enemy if too far from player
	bool canErase = false;
	list<Enemy>::iterator it;

// audio
	Audio audio;

	while(true)	{
		timerEnd = chrono::system_clock::now();
		timeLastSpawn = timerEnd - timerStart;
		if( timeLastSpawn.count() > 1 )
			if(timeLastSpawn.count() > MAX_SPAWN_TIME || canSpawn()){
				Enemy en(map.getBorder(), index);
				enemies.push_back(en);
				indexes.push_back(index);

				index++;
				timerStart = chrono::system_clock::now();
			}

/**
 * REPAINTING THE CAR (due to a bug with sfml)
*/
		car.display();

/**
 * CHECKING CONTROLS
*/
		if(kbhit()) c = getchar();	// avoid pressed char to be displayed on terminal when the program ends
		isAccelerating = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		isBraking = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		isRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		isLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) exit(0);

		carEnd = chrono::system_clock::now();
		seconds = carEnd - carStart;
		if(seconds.count() > 0.05)
		{
			if(isAccelerating){
				car.accelerate();
				if(canPlayAudio) audio.playAccelerate(car.getSpeed());
			}

			if(isBraking){
				car.brake();
				if(canPlayAudio) audio.playBrake(car.getSpeed());
			}
			if(isRight){ 
				if(car.getSpeed() > 0){
					car.turn(RIGHT);
					isLeft = false;
				} 
			}
			if(isLeft){
				if(car.getSpeed() > 0){
					car.turn(LEFT);
					isRight = false;
				} 
			}
			if(canPlayAudio && !isAccelerating && !isBraking) audio.playSame(car.getSpeed());
			carStart = chrono::system_clock::now();
		}


/**
 * UPDATING UI
*/		
		
		usleep( (MAX_SPEED_ALLOWED - car.getSpeed()) * 120 / car.getGear() );
		map.display(car.getSpeed());
		car.display();

		end = chrono::system_clock::now();
		canUpdate = false;
		for(auto &en : enemies)
		{
			seconds = end-start;
			if( seconds.count() >= 0.05){
				en.updatePos(car.getSpeed());
				canUpdate = true;
			}
			
			if(en.getCoord().x < 190 && en.getCoord().x > 0){
				en.display();
				if(en.isCollidingWith(car)){
					char backslash = 92;
					gameOver();
					exit(0);
				}
			}
			else if(en.getCoord().x < -150 || en.getCoord().x > 400){
				it = find(enemies.begin(), enemies.end(), en.getIndex());
				canErase = true;
			}
		
		}
		if(canErase){
			enemies.erase(it);
			canErase = false;
		}
		if(canUpdate){
			start = chrono::system_clock::now();
			canUpdate = false;
		}

		gotoxy(0, map.getBorder() + 5);
		std::cout << "Enemies: " << enemies.size();
		gotoxy(0, map.getBorder()+2);
		std::cout << "Speed: " << car.getSpeed() <<" | " << car.getMaxSpeed() << "   ";
	}
	// // cin.ignore();
	// // cin.get();
	return 0;
}
