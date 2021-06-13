#pragma once
#ifndef CHIP_H
#define CHIP_H
#include <iostream>
#include<list>
#include<string>
#include"polygon.h"
#include"layer.h"
#include<map>
using namespace std;

class Chip {
public:
	Chip();
	map<int, Layer> layer;
	void Insert_Layer(list<string > layerInfo);//Call Layer construtor function,and instert the object to the map_container in Chip
	void Insert_ploy(list<string > polyInfo);//Insert the polygon to its layer
	void setBoundary(list<string > chipInfo);
	bool checkBoundary();
	void Insert_Fill(int window_size);
	void print(ostream &outFile);
private:
	unsigned int Bottom_Left_X;
	unsigned int Bottom_Left_Y;
	unsigned int Top_Right_X;
	unsigned int Top_Right_Y;

};

#endif
