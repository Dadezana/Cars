#ifndef MENU_H
#define MENU_H
#define CHAR_OPZIONE_MAX 80

#include <iostream>
#include <string.h>
#include <SFML/Window.hpp>
#include <chrono>
#include "utils.h"

class Menu{

    const static int MENU_MAX = 20;
    const static int keyENTER = 10;
    const static int keyW = 119;
    const static int keyS = 115;
    const static int ARROW = 62;

    bool canPlayAudio = true;

    std::chrono::_V2::system_clock::time_point start = chrono::system_clock::now();
	std::chrono::_V2::system_clock::time_point end = chrono::system_clock::now();
	chrono::duration<double> seconds;

	int puntatore[MENU_MAX];
    char ascii;
	void interfaccia();

	int pos, numeroOpzioni;
	char opzioni[MENU_MAX][CHAR_OPZIONE_MAX];

	public:

		Menu(int Pos, char Opzioni[][CHAR_OPZIONE_MAX], int NumeroOpzioni){

			pos = Pos;
			numeroOpzioni = NumeroOpzioni;
			for(int i = 0; i < numeroOpzioni; i++) strcpy(opzioni[i], Opzioni[i]);
		};

		int intefacciaRisultato();
        void setAudio(bool a, int pos){
            canPlayAudio = a;
            if(canPlayAudio){
                strcpy(opzioni[pos], "Audio: Yes ");
            }else{
                strcpy(opzioni[pos], "Audio: No  ");
            }
        }
};

    int Menu::intefacciaRisultato(){

        for(int i = 0; i < numeroOpzioni; i++) puntatore[i] = 32;
        if(pos >= numeroOpzioni || pos < 0) pos = 0;
        puntatore[pos] = ARROW;

        do{
            end = chrono::system_clock::now();
            seconds = end - start;
            if(seconds.count() < 0.2){
                continue;
            }
            
            gotoxy(0, 0);
            interfaccia();
            ascii = ' ';
            if(kbhit()) int c = getchar();
            if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) ascii = keyS;
            else if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) ascii = keyW;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) ascii = keyENTER;
            
            if(ascii == keyW || ascii == keyW-32){

                puntatore[pos] = 32;
                pos--;

                if(pos == -1) pos = numeroOpzioni - 1;

                puntatore[pos] = ARROW;
                
                start = chrono::system_clock::now();

            }

            if(ascii == keyS || ascii == keyS-32){

                puntatore[pos] = 32;
                pos++;

                if(pos == numeroOpzioni) pos = 0;

                puntatore[pos] = ARROW;

                start = chrono::system_clock::now();

            }
        }while(ascii != keyENTER);
        return pos;
    }

    void Menu::interfaccia(){

        cout << "\n";
        for(int i = 0; i < numeroOpzioni; i++){

            cout <<"\t "<<char(puntatore[i])<<" "<<opzioni[i] << "\n";
        }
    }


#endif