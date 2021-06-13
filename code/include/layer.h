#pragma once
#ifndef LAYER_H
#define LAYER_H
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include "polygon.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
bool compare_X( Polygon& first, Polygon& second);
bool compare_Y( Polygon& first, Polygon& second);
bool compare_Y_big( Polygon& first, Polygon& second);

struct poly_In_Window{
	list<Polygon> window_poly;
	unsigned long long window_TotalArea;
};
struct free_space{
	int bl_x;
	int bl_y;
	int tr_x;
	int tr_y;
};
struct grid{
	int control = 0;
	long long area;
	unsigned int bl_x;
	unsigned int bl_y;
	unsigned int tr_x;
	unsigned int tr_y;
};
class Layer {
public:
	Layer();
	Layer(list<string > polygonInfo);
	list<Polygon> polygon;
	list<poly_In_Window> window;
	void Insert_Polygon(list<string > polygonInfo);//Call Polygon construtor function,and instert the object to the map container in Layer
	void space_divide(int,int,int,int,int,int);
	void insert_fill(int window_size,unsigned int Bottom_Left_X,unsigned int Bottom_Left_Y,unsigned int Top_Right_X,unsigned int Top_Right_Y);
	list<unsigned long long> window_TotalArea;
	void outputprint(ostream &outFile);
private:
	int Layer_id;
	string type;
	int min_width;
	int min_space;
	int max_fill_width;
	double min_density;
	double max_density;
	unsigned long long min_coverage=0;
	//list<free_space>;
};
#endif
