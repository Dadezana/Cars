#ifndef ANIM_H
#define ANIM_H

#include <iostream>
#include <fstream>
#include "utils.h"
using namespace std;
class Animation{

	private:
        const static u_int MAX = 100;   // static -> all the instances of the class share the same MAX value
		string camp[MAX];
		int frame;
		int weight, lenght;
		// string strisce= "      ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████           ██████";
		string strisce="██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ██████            ";
		int borderY;

	public:
		Animation();
		void load(string world = "graphics/map.txt");
		void display(int speed);
		int getBorder() { return borderY; }
};

#endif