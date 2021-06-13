#pragma once
#ifndef POLYGON_H
#define POLYGON_H
#include <iostream>
#include<list>
#include<string>

using namespace std;
static int total_id = 0;
class Polygon {
public:
	Polygon(int new_bl_X,int new_bl_Y,int new_tr_X,int new_tr_Y,int new_layer_id);
	Polygon(list<string > polygonInfo);
	long long  coverage(int window_size,int window_X,int window_Y);
	bool isOverlapped(int fill_size,int fill_X,int fill_Y,int buffer_size);
	int get_tr_X();
	int get_tr_Y();
	int get_bl_X();
	int get_bl_Y();
	void poly_outFile(ostream &outFile);
private:
	int Polygon_id;
	int bl_X;
	int bl_Y;
	int tr_X;
	int tr_Y;
	int net_id;
	int layer_id;
	string polygon_type;
};

#endif
