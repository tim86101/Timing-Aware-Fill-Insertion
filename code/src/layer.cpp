#include "layer.h"

Layer::Layer()
{
}

Layer::Layer(list<string> polygonInfo)
{
	list<string>::iterator it_polyInfo = polygonInfo.begin();
	Layer_id = stoi(*it_polyInfo);		++it_polyInfo;
	type = *it_polyInfo;			++it_polyInfo;
	min_width = stoi(*it_polyInfo);		++it_polyInfo;
	min_space = stoi(*it_polyInfo);		++it_polyInfo;
	max_fill_width = stoi(*it_polyInfo);	++it_polyInfo;
	min_density = stod(*it_polyInfo);	++it_polyInfo;
	max_density = stod(*it_polyInfo);
	min_coverage = 0;
}

void Layer::Insert_Polygon(list<string> polygonInfo)
{
	Polygon newPoly(polygonInfo);
	polygon.push_back(newPoly);
//	cout<<polygon.size();
//	cout<<"523 ";
}

void Layer::insert_fill(int window_size, unsigned int Bottom_Left_X, unsigned int Bottom_Left_Y, unsigned int Top_Right_X, unsigned int Top_Right_Y) {
	cout<<"insert layer "<<Layer_id<<endl;
	unsigned long long TotalArea = 0;
	list<int> insert_X;//we can insert
	list<int> insert_Y;
	int Max_X = 0;//the max tr_x
	int Max_Y = 0;
	unsigned long long min_coverage = window_size * window_size*min_density;
	int window_blX = Bottom_Left_X;
	int window_blY = Bottom_Left_Y;
	int window_trX = Bottom_Left_X + window_size;
	int window_trY = Bottom_Left_Y + window_size;
	TotalArea = 0;//initialize

	polygon.sort(compare_X);

//cout<<polygon.size()<<endl<<endl;
//
//
//	list<Polygon>::iterator it_sort = polygon.begin();//sorting test
//	while(it_sort != polygon.end()){
//		cout<<it_sort->get_bl_X()<<endl;
//		it_sort++;
//	}


	list<Polygon>::iterator it_poly = polygon.begin();//find polygon
	list<Polygon>::iterator it2_poly = ++polygon.begin();
//	list<Polygon>::iterator it3_poly = --polygon.end();
//	cout<<"X: ";
	while (it_poly != polygon.end()) {
	//	cout<<"111"<<endl;
		if (it_poly == polygon.begin()) {//in begining,save the boundary and first metal's bl_x
		//	cout<<"1 if :"<<Bottom_Left_X<<" , "<<it_poly->get_bl_X()<<endl;
			insert_X.push_back(Bottom_Left_X);
			insert_X.push_back(it_poly->get_bl_X());
		}
		if (it2_poly != polygon.end()) {//beside the last metal
			if (it_poly->get_tr_X() < it2_poly->get_bl_X()) {
					if(it_poly->get_tr_X() > Max_X){
					//	cout<<"2.1 if :"<<it_poly->get_tr_X()<<" , "<<it2_poly->get_bl_X()<<endl;
						insert_X.push_back(it_poly->get_tr_X());
						insert_X.push_back(it2_poly->get_bl_X());
					}
					else if (Max_X > it2_poly->get_bl_X()){
					//	cout<<"Not insert\n";
					}
					else{
					//	cout<<"2.2 if :"<<Max_X<<" , "<<it2_poly->get_bl_X()<<endl;
						insert_X.push_back(Max_X);
						insert_X.push_back(it2_poly->get_bl_X());
					}
			}
		}
		else {//the last metal
		//	cout<<"3 if :"<<it_poly->get_tr_X()<<" , "<<Top_Right_X<<endl;
			insert_X.push_back(it_poly->get_tr_X());
			insert_X.push_back(Top_Right_X);
		}
		if (it_poly->get_tr_X() > Max_X)
			Max_X = it_poly->get_tr_X();
//		if(it2_poly -> get_tr_X() > Max_X)
//			Max_X = it2_poly -> get_tr_X();
		it_poly++;
		it2_poly++;
	}
//	cout<<"X done\n";
	//sort y
	
	polygon.sort(compare_Y);	
	
	it_poly = polygon.begin();
	it2_poly = ++polygon.begin();
//	it3_poly = --polygon.end();
	// cout<<"sort y\n";
	while (it_poly != polygon.end()) {
		if (it_poly == polygon.begin()) {
			insert_Y.push_back(Bottom_Left_Y);
			insert_Y.push_back(it_poly->get_bl_Y());
		//	cout<<"1 if : "<<Bottom_Left_Y<<" "<<it_poly->get_bl_Y()<<endl;
		}
		if (it2_poly != polygon.end()) {
			if (it_poly->get_tr_Y() < it2_poly->get_bl_Y()) {
					if(it_poly->get_tr_Y() > Max_Y){
						insert_Y.push_back(it_poly->get_tr_Y());
						insert_Y.push_back(it2_poly->get_bl_Y());
				//		cout<<"2.1 if :"<<it_poly->get_tr_Y()<<" "<<it2_poly->get_bl_Y()<<endl;
					}
					else if (Max_Y > it2_poly->get_bl_Y()){
				//		cout<<"Not insert\n";
					}
					else{
						insert_Y.push_back(Max_Y);
						insert_Y.push_back(it2_poly->get_bl_Y());
				//		cout<<"2.2 if :"<<Max_Y<<" "<<it2_poly->get_bl_Y()<<endl;
					}
			}
		}
		else {
			insert_Y.push_back(it_poly->get_tr_Y());
			insert_Y.push_back(Top_Right_Y);
		//	cout<<"3 if :"<<it_poly->get_tr_Y()<<" "<<Top_Right_Y<<endl;
		
		}
		if (it_poly->get_tr_Y() > Max_Y)
			Max_Y = it_poly->get_tr_Y();
//		if(it2_poly -> get_tr_Y() > Max_Y)
//			Max_Y = it2_poly -> get_tr_Y();
		it_poly++;
		it2_poly++;
	}
//	cout<<"Y done \n";
	//for test
	list<int>::iterator it_X = insert_X.begin();
	list<int>::iterator it_Y = insert_Y.begin();
	for(;it_X!=insert_X.end();++it_X)
		cout<<*it_X<<"  ";
	cout<<endl<<endl<<endl;
	for(;it_Y!=insert_Y.end();++it_Y)
		cout<<*it_Y<<"   ";
	cout<<endl;

	
	list<int>::iterator it_blX = insert_X.begin();
	list<int>::iterator it_blY = insert_Y.begin();
	list<int>::iterator it_trX = ++insert_X.begin();
	list<int>::iterator it_trY = ++insert_Y.begin();
	if(insert_X.size() > 4 && insert_Y.size() > 4){
		while (it_trX != insert_X.end()) {
			it_blY = insert_Y.begin();
			it_trY = ++insert_Y.begin();

			while (it_trY != insert_Y.end()) {
				++(++it_blY);
				if (it_blY == insert_Y.end())
					break;
				++(++it_trY);
			}
			++(++it_blX);
			if (it_blX == insert_X.end())
				break;
			++(++it_trX);
		}
	}
	else if(insert_X.size() > 4){
		space_divide(min_width, max_fill_width, *it_blX+min_space , Bottom_Left_Y, *it_trX-min_space, Top_Right_Y);
	}
	else if(insert_Y.size() > 4){
		space_divide(min_width, max_fill_width, Bottom_Left_X, *it_blY+min_space, Top_Right_X, *it_trY-min_space);
	}


		//second fill
//	map<int, grid> grid_divide;
//	map<int, map<int, grid> > grid_divide_map;
	list<Polygon> fill_List;
	vector<int> ptr;

//	cout<<polygon.size();
	//long long need_to_insert = 100;
	polygon.sort(compare_X);
	
	list<Polygon>::iterator it_test = polygon.begin();
	while (window_trY <= Top_Right_Y) {
		window_blX = Bottom_Left_X;
		window_trX = window_blX + window_size;
			cout <<"  window Y= " << window_blY << endl;
		while (window_trX <= Top_Right_X) {
	//		cout << "Layer " << Layer_id << endl;
		//	cout << "window X= " << window_blX << "  window Y= " << window_blY << endl;
		//	cout<<"start to insert\n";	
			long long need_to_insert = 100;
			int fill_size = max_fill_width;// - 2 * min_space + 100;
			//keep reduce the grid size
			while (need_to_insert > 0 ) {
				if (fill_size < min_space)
					fill_size = min_space;
				int grid_width = fill_size + min_space * 2;
				
				int last_grid_width = (window_size % grid_width) + grid_width;
				
				int grid_num = window_size / grid_width;
			//	cout<<"fill size="<<fill_size<<endl;
			//	cout<<"grid wid"<<grid_width<<endl;
				int normal_area = fill_size * fill_size;
				int right_area = fill_size * (last_grid_width - 2 * min_space);
				int top_right_area = (last_grid_width - 2 * min_space) * (last_grid_width - 2 * min_space);
				
				map<int, map<int, grid> > grid_divide_map;
				map<int, grid> grid_divide;
				for (        int j = 0 ,grid_bl_y = window_blY; j < grid_num ;  ++j, grid_bl_y += grid_width  ) {//initial the grid info
					for (int i = 0 ,grid_bl_x = window_blX; i < grid_num ;  ++i, grid_bl_x += grid_width) {
					//	cout<<grid_bl_y<<" "<<grid_bl_x<<endl;
						grid newgrid;
						newgrid.control = 0;
						if (i != grid_num - 1  && j != grid_num - 1 ) {
							newgrid.area = normal_area;
							newgrid.bl_x = grid_bl_x;
							newgrid.bl_y = grid_bl_y;
							newgrid.tr_x = grid_bl_x + grid_width;
							newgrid.tr_y = grid_bl_y + grid_width;
						}
						else if (i != grid_num - 1 && j == grid_num - 1 ) {//top most
							newgrid.area = right_area;
							newgrid.bl_x = grid_bl_x;
							newgrid.bl_y = grid_bl_y;
							newgrid.tr_x = grid_bl_x + grid_width;
							newgrid.tr_y = window_trY;
						}
						else if (i == grid_num - 1  && j != grid_num - 1 ) {//right most
							newgrid.area = right_area;
							newgrid.bl_x = grid_bl_x;
							newgrid.bl_y = grid_bl_y;
							newgrid.tr_x = window_trX;
							newgrid.tr_y = grid_bl_y + grid_width;
						}
						else {//top right
							newgrid.area = top_right_area;
							newgrid.bl_x = grid_bl_x;
							newgrid.bl_y = grid_bl_y;
							newgrid.tr_x = window_trX;
							newgrid.tr_y = window_trY;
						}

						grid_divide.insert(pair<int, grid>(i, newgrid));
					}
					grid_divide_map.insert(pair<int, map<int, grid> >(j, grid_divide));
					grid_divide.clear();
				}
				list<Polygon>::iterator it_poly = polygon.begin();
				long long Total_area_in_window = 0;
				long long overlape_window = 0;
				
				unsigned int lastgrid_blx=window_trX - last_grid_width;
				unsigned int lastgrid_bly=window_trY - last_grid_width;
			//	cout<<"overlaping check\n";
				while (it_poly != polygon.end()) {
					if (it_poly->get_bl_X() > window_trX) {
						break;
					}
					else {
						overlape_window = it_poly->coverage(window_size, window_blX, window_blY);
						if (overlape_window > 0) {
							Total_area_in_window += overlape_window;
						//	cout<<"overlape_window"<<overlape_window<<endl;
							int grid_x_begin = (it_poly->get_bl_X() > window_blX)
								? floor(float((it_poly->get_bl_X() - window_blX)) / float(grid_width))
								: 0;
						//	cout<<"xbegin"<<grid_x_begin<<endl;
							int grid_x_end = (it_poly->get_tr_X() <= lastgrid_blx)
								? ceil(float((it_poly->get_tr_X() - window_blX)) / float(grid_width))
								: grid_num;
						//	cout<<"xend"<<grid_x_end<<endl;
						//
						//
							int grid_y_begin = (it_poly->get_bl_Y() > window_blY)
								? floor(float((it_poly->get_bl_Y() - window_blY)) / float(grid_width))
								: 0;
						//	cout<<"ybegin"<<grid_y_begin<<endl;
							int grid_y_end = (it_poly->get_tr_Y() <= lastgrid_bly)
								? ceil(float((it_poly->get_tr_Y() - window_blY)) / float(grid_width ))
								: grid_num;
							if(grid_x_begin == grid_num)
								grid_x_begin -= 1;
							if(grid_y_begin == grid_num)
								grid_y_begin -= 1;

							if(grid_x_end > grid_num)
								grid_x_end = grid_num;
							if(grid_y_end > grid_num)
								grid_y_end = grid_num;
							
						//	cout<<"dd"<<grid_num;
						//	cout<<"yend"<<grid_y_end<<endl;
						//	cout<<it_poly->get_tr_Y()<<" ";
						//	cout<window_blY<<" ";
						//	cout<<grid_width<<" "<<endl;
						//	cout<<"ceil"<<ceil(float((it_poly->get_tr_Y() - window_blY)) / float(grid_width));
							map<int, grid>::iterator it_x;
							map< int, map < int, grid > >::iterator it_y;
							for (int j = grid_y_begin; j < grid_y_end; ++j) {
								it_y = grid_divide_map.find(j);
								for (int i = grid_x_begin; i < grid_x_end; ++i) {
									it_x = it_y->second.find(i);
									it_x->second.control = 1;
								}
							}

						}
					}
					++it_poly;
				}
				//new fill overlaping checking
			//	cout<<"fill overlaped check\n";
				fill_List.sort(compare_X);//:modify
				
				it_poly = fill_List.begin();
			//	list<Polygon>::iterator it_test = fill_List.begin();
			//	while(it_test != fill_List.end()){
			//		cout<<it_test->get_bl_X()<<endl;
			//		++it_test;
			//	}
				overlape_window = 0;
				while (it_poly != fill_List.end()) {
					if (it_poly->get_bl_X() > window_trX) {
						break;
					}
					else {
						overlape_window = it_poly->coverage(window_size, window_blX, window_blY);
						if (overlape_window > 0) {
							Total_area_in_window += overlape_window;
							int grid_x_begin = (it_poly->get_bl_X() > window_blX)
								? floor(float((it_poly->get_bl_X() - window_blX)) / float(grid_width))
								: 0;
							int grid_x_end = (it_poly->get_tr_X() <= lastgrid_blx)
								? ceil(float((it_poly->get_tr_X() - window_blX)) / float(grid_width))
								: grid_num;
											

							int grid_y_begin = (it_poly->get_bl_Y() > window_blY)
								? floor(float((it_poly->get_bl_Y() - window_blY)) / float(grid_width))
								: 0;
							int grid_y_end = (it_poly->get_tr_Y() <= lastgrid_bly)
								? ceil(float((it_poly->get_tr_Y() - window_blY)) / float(grid_width))
								: grid_num;
							if(grid_x_begin == grid_num)
								grid_x_begin -= 1;
							if(grid_y_begin == grid_num)
								grid_y_begin -= 1;
							if(grid_x_end > grid_num)
								grid_x_end = grid_num;
							if(grid_y_end > grid_num)
								grid_y_end = grid_num;
							map<int, grid>::iterator it_x;
							map< int, map < int, grid > >::iterator it_y;
							for (int j = grid_y_begin; j < grid_y_end; ++j) {
								it_y = grid_divide_map.find(j);
								for (int i = grid_x_begin; i < grid_x_end; ++i) {
									it_x = it_y->second.find(i);
									it_x->second.control = 1;
								}
							}

						}
					}
					++it_poly;
				}
				//end
				need_to_insert = min_coverage - Total_area_in_window;
				if (min_coverage > Total_area_in_window) {
				//	need_to_insert = min_coverage - Total_area_in_window;
					srand(time(NULL));
					//take the free grid out to the new map
					map<int, grid> random_array;
					int count = 0;
					map<int, grid>::iterator it_x;
					map<int, map<int, grid> >::iterator it_y;
					for (int j = 0; j < grid_num; ++j) {
						it_y = grid_divide_map.find(j);
						for (int i = 0; i < grid_num; ++i) {
							it_x = it_y->second.find(i);
							if (it_x->second.control == 0) {
						//		cout<<"("<<i<<","<<j<<")";
						//		cout<<"blx ="<<it_x->second.bl_x<<endl;
						//		cout<<"bly ="<<it_x->second.bl_y<<endl;
						//		cout<<"trx ="<<it_x->second.tr_x<<endl;
						//		cout<<"try ="<<it_x->second.tr_y<<endl;
								grid random_grid=it_x->second;
								random_array[count] = random_grid;
								++count;
							}
						}
					//	cout<<endl;
					}
				//	cout<<"\n\n";
					
					int random_size = random_array.size();
					if(random_size != 0){
					//start suffling
						ptr.resize( random_size );
						for (int i = 0; i < random_size; ++i)
							ptr[i] = i;
						for (int i = 0; i < random_size; ++i) {
							int pos1 = rand() % random_size;
							int pos2 = rand() % random_size;
							swap(ptr[pos1], ptr[pos2]);
						}
					//suffle end
						int insert_number = 0;
				//		cout << "need_to_insert: " << need_to_insert << endl;
						map<int, grid>::iterator it_rand;
						while (need_to_insert > 0 && insert_number < random_size) {
							it_rand = random_array.find( ptr [ insert_number ] );
						//	if(fill_size < max_fill_width/2){
							int newpoly_blx = it_rand->second.bl_x + min_space;
								int newpoly_bly = it_rand->second.bl_y + min_space;
								int newpoly_trx = it_rand->second.tr_x - min_space;
								int newpoly_try = it_rand->second.tr_y - min_space;
								if(((newpoly_trx - newpoly_blx <= max_fill_width) && ((newpoly_trx - newpoly_blx) >= min_width)) && (((newpoly_try - newpoly_bly) <= max_fill_width) && ((newpoly_try - newpoly_bly) >= min_width))){
									Polygon newpoly(newpoly_blx, newpoly_bly, newpoly_trx, newpoly_try, Layer_id);
									fill_List.push_back(newpoly);
									need_to_insert -= it_rand->second.area;
								}
					//		}
								++insert_number;
						}
						random_array.clear();
//					cout << "still need: " << need_to_insert << endl << endl <<endl;
					}
				}
				if(fill_size == min_width && need_to_insert > 0){
					cout<<"			need_to_insert = "<<need_to_insert<<endl;
					need_to_insert = 0;
					cout <<"		window X= " << window_blX << endl;
					cout<<"not enough!!!!!!\n";
				}
				else
					fill_size -= 1;
			}
//			cout<<"next X\n\n\n\n";
			window_blX += window_size / 2;
			window_trX += window_size / 2;
		}
		//merge two list

		fill_List.sort(compare_X);//modify
		list<Polygon>::iterator it_polyList = polygon.begin();
		list<Polygon>::iterator it_fillList = fill_List.begin();

		while (it_polyList != polygon.end() || it_fillList != fill_List.end()) {
			if (it_polyList != polygon.end() && it_fillList != fill_List.end()) {
				if (it_polyList->get_bl_X() > it_fillList->get_bl_X()) {
					it_polyList = polygon.insert(it_polyList, *it_fillList);
					++it_fillList;
					++it_polyList;
				}
				else {
					++it_polyList;
				}
			}
			else if (it_polyList == polygon.end() && it_fillList != fill_List.end()) {//fill List insert not finished , polyList is done
				it_polyList = polygon.insert(it_polyList, *it_fillList);
				++it_fillList;
				++it_polyList;
			}
			else {//fill list insert complete
				break;
			}

		}
		
//		list<Polygon>::iterator it_test = polygon.begin();
//		while(it_test != polygon.end()){
//			cout<<it_test->get_bl_X()<<endl;
//			++it_test;
//		}
	
		fill_List.clear();
	
		//merge end
		window_blY += window_size / 2;
		window_trY += window_size / 2;
	}


}
void Layer::space_divide(int min_width, int max_fill_width, int it_blX, int it_blY, int it_trX, int it_trY) {
	//cout<<"space divide<<endl";	
	int length = it_trX - it_blX;
	int width = it_trY - it_blY;
	int begin_X = it_blX;
//	int begin_Y = it_blY;
//	cout<<"length = "<<length<<endl;
//	cout<<"width = "<<width<<endl;
	if (length >= min_width && width >= min_width) {
		if (length <= max_fill_width && width <= max_fill_width) {
			Polygon newpoly(it_blX, it_blY, it_trX, it_trY, Layer_id);
			polygon.push_back(newpoly);
//			cout<<"112"<<endl;
		}
		else if (length > max_fill_width && width <= max_fill_width) {//X is over limit

			while (length >= min_width) {
				if (length >= max_fill_width) {
					Polygon newpoly(it_blX, it_blY, it_blX + max_fill_width, it_trY, Layer_id);
					polygon.push_back(newpoly);
//			cout<<"112"<<endl;
					length -= (max_fill_width + min_space);
					it_blX += (max_fill_width + min_space);
				}
				else {
					Polygon newpoly(it_blX, it_blY, it_trX, it_trY, Layer_id);
//			cout<<"112"<<endl;
					length = 0;
					polygon.push_back(newpoly);
				}
			}
		}
		else if (length <= max_fill_width && width > max_fill_width) {//Y is over limit
			while (width >= min_width) {
				if (width >= min_width) {
					Polygon newpoly(it_blX, it_blY, it_trX, it_blY + max_fill_width, Layer_id);
					polygon.push_back(newpoly);
//			cout<<"112"<<endl;
					width -= (max_fill_width + min_space);
					it_blY += (max_fill_width + min_space);
				}
				else {
					Polygon newpoly(it_blX, it_blY, it_blX, it_trY, Layer_id);
					polygon.push_back(newpoly);
//			cout<<"112"<<endl;
					width = 0;
				}
			}
		}
		else {//X,Y are bigger than the limit
			cout<<"X Y over\n";
			while (width >= min_width) {
				it_blX = begin_X;
				length = it_trX - it_blX;
				while (length >= min_width) {
					if (length >= max_fill_width) {
						if (width >= max_fill_width) {
							Polygon newpoly(it_blX, it_blY, it_blX + max_fill_width, it_blY + max_fill_width, Layer_id);
							polygon.push_back(newpoly);
//			cout<<"112"<<endl;
							length -= (max_fill_width + min_space);
							it_blX += (max_fill_width + min_space);
						}
						else {
							Polygon newpoly(it_blX, it_blY, it_blX + max_fill_width, it_trY, Layer_id);
							width = 0;
							polygon.push_back(newpoly);
						}
					}
					else {
						if (width >= max_fill_width) {
							Polygon newpoly(it_blX, it_blY, it_trX, it_blY + max_fill_width, Layer_id);
							length = 0;
							polygon.push_back(newpoly);
//			cout<<"112"<<endl;
						}
						else {
							Polygon newpoly(it_blX, it_blY, it_trX, it_trY, Layer_id);
							length = 0;
							width = 0;
							polygon.push_back(newpoly);
//			cout<<"112"<<endl;
						}
					}
				}
				width -= (max_fill_width + min_space);
				it_blY += (max_fill_width + min_space);
			}
		}
	}
}
bool compare_X(Polygon& first, Polygon& second) {
	if (first.get_bl_X()<second.get_bl_X()) {
		return true;
	}
	else
		return false;
}
bool compare_Y(Polygon& first, Polygon& second) {
	if (first.get_bl_Y()<second.get_bl_Y()) {
		return true;
	}
	else
		return false;
}
bool compare_Y_big(Polygon& first, Polygon& second) {
	if (first.get_tr_Y()>second.get_tr_Y()) {
		return true;
	}
	else
		return false;
}
void Layer::outputprint(ostream &outFile) {
	list<Polygon>::iterator it_poly = polygon.begin();
	while (it_poly != polygon.end()) {
		it_poly->poly_outFile(outFile);
		it_poly++;
	}
}
