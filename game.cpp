#include <iostream>
#include <string>
#include <list>
#include <time.h>
#include <chrono>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <sys/ioctl.h>	// get terminal size

#include "car.h"
#include "animation.h"
#include "enemy.h"
#include "menu.h"
#include "audio.h"
#define RIGHT true
#define LEFT false
using namespace std;

bool canSpawn(bool reset = false){
	srand(time(NULL));
// determine if we can decrease max and min time
	static auto spawnStart = chrono::system_clock::now();
	static auto spawnEnd = chrono::system_clock::now();
	spawnEnd = chrono::system_clock::now();
	chrono::duration<double> secs = spawnEnd - spawnStart;

// used to determine if its time to spawn an enemy
	static auto timerStart = chrono::system_clock::now();
	static auto timerEnd = chrono::system_clock::now();
	timerEnd = chrono::system_clock::now();
	chrono::duration<double> timer = timerEnd - timerStart;

	static int maxTime = 9;
	static int minTime = 4;
	if(reset){
		maxTime = 9;
		minTime = 4;
		timerStart = chrono::system_clock::now();
		spawnStart = chrono::system_clock::now();
		return false;
	}
	// // gotoxy(0, 42);
	// // cout << "minTime: " << minTime << "\nmaxTime: " << maxTime;
	static int spawnTime = minTime + rand()%(maxTime+1 - minTime);

	if( secs.count() > 10 ){
		if(maxTime > 3) maxTime--;
		if(minTime > 0) minTime--;
		spawnStart = chrono::system_clock::now();
	}
	if(timer.count() >= spawnTime){
		timerStart = chrono::system_clock::now();
		spawnTime = minTime + rand()%(maxTime+1 - minTime);
		return true;
	}
	return false;
	// // return (rand()%maxTime) % 10 == 0;

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

	cout << RED;
	gotoxy(70, 15);
	cout << " ___  _        _  _        ___  __ _        _         ___      / /    _  _                \\ \\  ";
	gotoxy(70, 16);
	cout << "| _ \\| | __ _ | || |      /   \\/ _` | __ _ (_) _ _   |__ \\    | |    | || |   _     _ _    | | ";
	gotoxy(70, 17);
	cout << "|  _/| |/ _` | \\_. |      | - |\\__. |/ _` || || ' \\    /_/    | |     \\_. |  ( )   | ' \\   | |  ";
	gotoxy(70, 18);
	cout << "|_|  |_|\\__/_| |__/       |_|_||___/ \\__/_||_||_||_|  (_)      \\_\\_   |__/   |/    |_||_| /_/   ";
	cout << RESET;
}

bool playAgain(){
	
	sleep(1);
	while(true){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) return true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)) return false;
	}
}

int main(){

	bool canPlayAudio = true;
	const int MAX_SPEED_ALLOWED = 200;
	bool play = true;
	bool crashed = false;
	Audio audio;
	system("clear");
/**
 * MAIN MENU
*/

	const int NUM_OPTIONS = 3;
	char options[NUM_OPTIONS][CHAR_OPZIONE_MAX];
	strcpy(options[0], "Play");
	strcpy(options[1], "Audio: Yes");
	strcpy(options[2], "Quit");
	Menu a(0, options, NUM_OPTIONS);

	auto audioStart = chrono::system_clock::now();
	auto audioEnd = chrono::system_clock::now();
	chrono::duration<double> audioSec;

	while(true){
		int chose = a.intefacciaRisultato();
		audioEnd = chrono::system_clock::now();
		audioSec = audioEnd - audioStart;

		if(chose == 0){
			if(!gameFit()){
				gotoxy(0, 0);
				cout << BOLDRED << "The game won't fit in your terminal. Decrease the zoom, or set the window to fullscreen and try again" << RESET;
				continue;
			}
			break;

		}else if(chose == 1 && audioSec.count() > 0.3){
			canPlayAudio = !canPlayAudio;
			a.setAudio(canPlayAudio, 1);
			if(canPlayAudio) audio.setVolume(60);
			else audio.setVolume(0);
			audioStart = chrono::system_clock::now();

		}else if(chose == 2){
			exit(0);
		}	
	}
	
	while(play){
/**
 * SETTING UP THE GAME
*/

		Animation map;
		Car car;
		car.setBorder(map.getBorder());

		int index = 0;
		list<Enemy> enemies;	// other cars spawning
		for(int i = 0; i < enemies.size(); i++){
			enemies.pop_back();
		}

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
		canSpawn(true);

	// deleting an enemy if too far from player
		bool canErase = false;
		list<Enemy>::iterator it;

	// player's score
		int points = 0;
		auto startPoints = chrono::system_clock::now();
		auto endPoints = chrono::system_clock::now();
		chrono::duration<float> secPoints;

	// avoid calling chrono::system_clock::now() multiple times
		auto current_time = chrono::system_clock::now();

		while(true)	{

			current_time = chrono::system_clock::now();

			timerEnd = current_time;
			timeLastSpawn = timerEnd - timerStart;
			if( timeLastSpawn.count() > 1 )
				if(canSpawn()){
					Enemy en(map.getBorder(), index);
					enemies.push_back(en);

					index++;
					timerStart = current_time;
				}


	// Repainting the car (due to a bug with sfml)
			car.display();
	// Updating score
			endPoints = current_time;
			secPoints = endPoints - startPoints;
			if(secPoints.count() >= 0.3){
				startPoints = current_time;
				if(car.getSpeed() > 100) points += car.getSpeed()/20; // min speed to get points: 100
			}
			gotoxy(0, map.getBorder() + 3);
			cout << "Points: " << points << "  ";

	/**
	 * CHECKING CONTROLS
	*/
			if(kbhit()) c = getchar();	// avoid pressed char to be displayed on terminal when the program ends
			isAccelerating = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			isBraking = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			isRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			isLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){			// pause
				audio.stopAllSounds();
				sleep(1);
				while(true){
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
						sleep(1);
						break;
					}
					continue;
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) audio.playHorn();

			current_time = chrono::system_clock::now();

			carEnd = current_time;
			seconds = carEnd - carStart;
			if(seconds.count() > 0.05)
			{
				if(isAccelerating){
					car.accelerate();
					audio.playAccelerate(car.getSpeed());
				}

				if(isBraking){
					car.brake();
					audio.playBrake(car.getSpeed());
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
				if(!isAccelerating && !isBraking) audio.playSame(car.getSpeed());
				carStart = current_time;
			}


	/**
	 * UPDATING UI
	*/		
			
			usleep( (MAX_SPEED_ALLOWED - car.getSpeed()) * 120 / car.getGear() );
			map.display(car.getSpeed());
			car.display();

			end = current_time;
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
						gameOver();					// 2 times because sfml doesn't allow him to paint the first time
						gameOver();
						audio.playCrash();
						crashed = true;
						if(playAgain()){
							play = true;
							break;
						}
						play = false;
						exit(0);
					}
				}
				else if(en.getCoord().x < -150 || en.getCoord().x > 400){
					it = find(enemies.begin(), enemies.end(), en.getIndex());
					canErase = true;
				}
			
			}
			if(crashed){
				crashed = false;
				break;
			}
			if(canErase){
				enemies.erase(it);
				canErase = false;
			}
			if(canUpdate){
				start = current_time;
				canUpdate = false;
			}

			// // gotoxy(0, map.getBorder() + 5);
			// // cout << "Enemies: " << enemies.size();
			gotoxy(0, map.getBorder()+2);
			std::cout << "Speed: " << car.getSpeed() <<" | " << car.getMaxSpeed() << "   ";
		}
	}
	// // cin.ignore();
	// // cin.get();
	return 0;
}
