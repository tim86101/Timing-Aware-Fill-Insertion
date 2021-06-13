#include "polygon.h"
Polygon::Polygon(int new_bl_X,int new_bl_Y,int new_tr_X,int new_tr_Y,int new_layer_id){
	Polygon_id=total_id+1;
	bl_X=new_bl_X;
	bl_Y=new_bl_Y;
	tr_X=new_tr_X;
	tr_Y=new_tr_Y;
	net_id=0;
	layer_id=new_layer_id;
	polygon_type="Fill";
	total_id++;
//	cout<<total_id<<endl;
	//cout<<"insert fill\n";
}
Polygon::Polygon(list<string> polygonInfo)
{
	list<string>::iterator it_polyinfo = polygonInfo.begin();
	Polygon_id = stoi(*it_polyinfo);++it_polyinfo; 
	bl_X = stoi(*it_polyinfo);	++it_polyinfo;
	bl_Y = stoi(*it_polyinfo);  	++it_polyinfo;
	tr_X = stoi(*it_polyinfo);  	++it_polyinfo;
	tr_Y = stoi(*it_polyinfo);  	++it_polyinfo;
	net_id = stoi(*it_polyinfo);	++it_polyinfo;
	layer_id = stoi(*it_polyinfo);	++it_polyinfo;
	polygon_type = *it_polyinfo;
	total_id = (Polygon_id > total_id) ? Polygon_id : total_id;
	//cout<<total_id<<endl;
}
long long Polygon::coverage(int window_size,int window_X,int window_Y){

	int window_bl_X=window_X;
	int window_bl_Y=window_Y;
	int window_tr_X=window_X + window_size;
	int window_tr_Y=window_Y + window_size;

	int p_blx = max(bl_X, window_bl_X);
	int p_bly = max(bl_Y, window_bl_Y);
	
	int p_trx = min(tr_X, window_tr_X);
	int p_try = min(tr_Y, window_tr_Y);

	long long join = 0;
	if( p_trx> p_blx && p_try > p_bly){
		join = (p_trx - p_blx)*(p_try - p_bly);    
		return join;
	}
	else
		return 0;
}


bool Polygon::isOverlapped(int fill_size,int fill_X,int fill_Y,int buffer_size){

	int fill_bl_X=fill_X-fill_size;
	int fill_bl_Y=fill_Y-fill_size;
	int fill_tr_X=fill_X;
	int fill_tr_Y=fill_Y;
	int new_poly_bl_X=bl_X+buffer_size;
	int new_poly_bl_Y=bl_Y+buffer_size;
	int new_poly_tr_X=tr_X+buffer_size;
	int new_poly_tr_Y=tr_Y+buffer_size;
	if(fill_tr_X>=new_poly_tr_X&&new_poly_bl_X>=fill_bl_X){
		if(fill_tr_Y>=new_poly_tr_Y&&new_poly_bl_Y>fill_bl_Y){
			return true;
		}
		else if(new_poly_tr_Y>fill_tr_Y&&fill_tr_Y>new_poly_bl_Y){
			return true;
		}
		else if(new_poly_tr_Y>fill_bl_Y&&fill_bl_Y>new_poly_bl_Y){
			return true;
		}
		else {
			return false;
		}
	}
	else if(new_poly_tr_X>fill_bl_X&&fill_bl_X>new_poly_bl_X){
		if(fill_tr_Y>=tr_Y&&new_poly_bl_Y>fill_bl_Y){
			return true;
		}
		else if(new_poly_tr_Y>fill_tr_Y&&fill_tr_Y>new_poly_bl_Y){
			return true;
		}
		else if(new_poly_tr_Y>fill_bl_Y&&fill_bl_Y>new_poly_bl_Y){
			return true;
		}
		else {
			return false;
		}
	}
	else if(new_poly_tr_X>fill_tr_X&&fill_tr_X>new_poly_bl_X){
		if(fill_tr_Y>=new_poly_tr_Y&&new_poly_bl_Y>fill_bl_Y){
			return true;
		}
		else if(new_poly_tr_Y>fill_tr_Y&&fill_tr_Y>new_poly_bl_Y){
			return true;
		}
		else if(new_poly_tr_Y>fill_bl_Y&&fill_bl_Y>new_poly_bl_Y){
			return true;
		}
		else {
			return false;
		}
	}
	else
		return false;



}

int Polygon::get_tr_X(){
	return tr_X;
}
int Polygon::get_tr_Y(){
	return tr_Y;
}
int Polygon::get_bl_X(){return bl_X;}
int Polygon::get_bl_Y(){return bl_Y;}
void Polygon::poly_outFile(ostream &outFile){
//	if(polygon_type == "Fill")
		outFile<<Polygon_id<< " "<<bl_X<<" "<<bl_Y<<" "<<tr_X<<" "<<tr_Y<<" "<<net_id<<" "<<layer_id<<" "<<polygon_type<<endl;
}
