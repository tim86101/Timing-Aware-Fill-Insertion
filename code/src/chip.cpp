#include "chip.h"
#include<string>
Chip::Chip()
{
	Bottom_Left_X = 0;
	Bottom_Left_Y = 0;
	Top_Right_X = 0;
	Top_Right_Y = 0;
}

void Chip::Insert_Layer(list<string> layerInfo)
{
	list<string>::iterator it_layerinfo = layerInfo.begin();
	int layerID = stoi(*it_layerinfo);
	Layer newlayer(layerInfo);
	layer.insert(pair<int, Layer>(layerID, newlayer));
}

void Chip::Insert_ploy(list<string> polyInfo)
{
	list<string>::reverse_iterator it_polyInfo = ++polyInfo.rbegin();
	int poly_locate_layer = stoi(*it_polyInfo);
	map<int, Layer>::iterator inserting_layer;
	layer[poly_locate_layer].Insert_Polygon(polyInfo);

}

void Chip::setBoundary(list<string> chipInfo)
{
	list<string>::iterator it_chipInfo = chipInfo.begin();
	Bottom_Left_X = stoi(*it_chipInfo);  ++it_chipInfo; 
	Bottom_Left_Y = stoi(*it_chipInfo);  ++it_chipInfo; 
	Top_Right_X = stoi(*it_chipInfo);  ++it_chipInfo;
	Top_Right_Y = stoi(*it_chipInfo);
}

bool Chip::checkBoundary()
{
	return false;
}

void Chip::Insert_Fill(int window_size){
	
//	cout<<"enter 1  "<<endl;
//	layer[5].insert_fill(window_size,Bottom_Left_X,Bottom_Left_Y,Top_Right_X,Top_Right_Y);

//	layer[9].insert_fill(window_size,Bottom_Left_X,Bottom_Left_Y,Top_Right_X,Top_Right_Y);

	layer[1].insert_fill(window_size,Bottom_Left_X,Bottom_Left_Y,Top_Right_X,Top_Right_Y);

//	for(unsigned int i=1;i<=layer.size();i++){
//		layer[i].insert_fill(window_size,Bottom_Left_X,Bottom_Left_Y,Top_Right_X,Top_Right_Y);
//	}
	
}

void Chip::print(ostream &outFile){
	for(unsigned int i=1;i<=layer.size();i++){
		layer[i].outputprint(outFile);
	}


}
