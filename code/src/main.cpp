#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<list>
#include"chip.h"
#include"polygon.h"
#include"layer.h"
#include<map>
#include <stdio.h>
#include <vector>
using namespace std;
#define Max 1000
void Load_configFile(char *fileName);
void Load_layoutFile(string layout_fileName, string rule_fileName);
void Load_ruleFile(string fileName);
void Load_processFile(string fileName);
string spilt_InputPath(char* fileName);
string spilt_OutputPath(char* fileName);
	
struct layer{//table
	string capacitance_first;//area_table_1_0 
	string capacitance_second;//*
};

struct table_data{//table_index
	string tableName;
	vector<double> range;
	vector<string> range_index_a;
	vector<string> range_index_b;
};


list<string> strtoken(char str[]);

map<int, int> critical_net;
map<int, int> power_net;
map<int, int> groud_net;

map<int,map<int,layer> > layer_column;
map<int,layer> layer_row;
map<string,table_data> table_index;

int window_size;
string fill_fileName;


Chip chip;
int main(int argc,char **argv) {
//	cout<<"123";
	Load_configFile(argv[1]);
	chip.Insert_Fill(window_size);
	ofstream outFile(fill_fileName,ios::out);
	if(!outFile){
		cout<<"File could not be opened"<<endl;
		exit(1);
	}
	else
		chip.print(outFile);
		
	
	outFile.close();
	
}
void Load_configFile(char *fileName){
	string inputPath = spilt_InputPath(fileName);
	string layout_fileName = inputPath;
	string rule_fileName = inputPath;
	string process_fileName = inputPath;
	fill_fileName = spilt_OutputPath(fileName);
	fstream infile;
	char input[Max] = {};
	infile.open(fileName, ios::in);
	if (!infile)
		cout << "Failed to open config file." << endl;
	else {
		for (int i = 0; i < 7; i++) {
			infile.getline(input, sizeof(input), '\n');
			list<string> net;
			switch (i)
			{
			case 0: {
				layout_fileName += *(strtoken(input).rbegin());
				break;
			}
			case 1: {
				fill_fileName += *(strtoken(input).rbegin());
				break;
			}
			case 2: {
				rule_fileName += *(strtoken(input).rbegin());
				break;
			}
			case 3: {
				process_fileName += *(strtoken(input).rbegin());
				break;
			}
			case 4: {
				net = strtoken(input);
				list<string>::iterator it_net = ++net.begin();
				while (it_net != net.end()) {
					critical_net[stoi(*it_net)] = stoi(*it_net);
					++it_net;
				}
			}
			case 5: {
				net = strtoken(input);
				list<string>::iterator it_net = ++net.begin();
				while (it_net != net.end()) {
					power_net[stoi(*it_net)] = stoi(*it_net);
					++it_net;
				}
			}
			case 6: {
				net = strtoken(input);
				list<string>::iterator it_net = ++net.begin();
				while (it_net != net.end()) {
					groud_net[stoi(*it_net)] = stoi(*it_net);
					++it_net;
				}
			}
			default:
				break;
			}
		}
	}
	infile.close();
	Load_layoutFile(layout_fileName, rule_fileName);
	Load_processFile(process_fileName);
}

void Load_layoutFile(string layout_fileName, string rule_fileName){
	ifstream infile;
	list<string> layoutInfo;
	infile.open(layout_fileName, ios::in);
	if (!infile)
		cout << "Fail to open File" << endl;
	else{
		char input[Max];
		infile.getline(input, sizeof(input), '\n');
		chip.setBoundary(strtoken(input));
	//	cout<<"ready to enter load rule 123"<<endl;
		Load_ruleFile(rule_fileName);
	
		while (infile.getline(input, sizeof(input), '\n')) {
		//	cout<<input<<endl;
			layoutInfo=strtoken(input);
			chip.Insert_ploy(layoutInfo);
		}
	}
	infile.close();
}

void Load_ruleFile(string fileName){
	ifstream infile;
	list<string> layoutInfo;
	infile.open(fileName, ios::in);
	if (!infile)
		cout << "Fail to open File" << endl;
	else{
		char input[Max];
		while (infile.getline(input, sizeof(input), '\n')) {
			if(input[0]!='\0'){
				chip.Insert_Layer(strtoken(input));
			}
		}
	}
	infile.close();
}

void Load_processFile(string fileName){
	ifstream infile;
	infile.open(fileName, ios::in);
	if (!infile)
		cout << "Fail to open file" << endl;
	else{
		char buffer[Max]={};
		int layer_nums;
		int layer_count_row = 0;
		int layer_count = 1;
		int range_size;
		table_data newnode;
		while (infile.getline(buffer, sizeof(buffer), '\n')){
			if (buffer[0] != ';' && buffer[0] != '\0'){//";"is a comment	
				list<string>::iterator it_inData ;
				if(buffer[0] == 'w'){		//parse window
					list<string> inData;
					inData = strtoken(buffer);
					it_inData = ++inData.begin();
					window_size=stoi(*it_inData);
				}
				else if(buffer[0] == ' '){  //parse table
					list<string> inData;
					inData = strtoken(buffer);
					layer_nums = inData.size();
				}
				else if(buffer[0]-'0' == layer_count_row){  //parse table
					list<string> inData;
					inData = strtoken(buffer);
					it_inData = inData.begin();
					++it_inData;
					list<string>::iterator it2_inData = ++inData.begin();
					layer_count = 1;
					for(++it2_inData,++it_inData;it2_inData!=inData.end();++it2_inData,++it_inData){
						layer newnode;
						newnode.capacitance_first = *it_inData;
						newnode.capacitance_second = *it2_inData;
						if(layer_count != layer_nums){
							++it_inData;
							++it2_inData;
						}
						layer_row.insert(pair<int,layer>(layer_count,newnode));
						if(layer_count == layer_nums)
							layer_column.insert(pair<int,map<int,layer> >(layer_count_row,layer_row));
						layer_count++;	
					}
					layer_count_row++;
					layer_row.clear();
				}
				else if(buffer[0] == 'T'){
					list<string> inData;
					inData = strtoken(buffer);
					it_inData = inData.begin();
					++it_inData;
					newnode.tableName = *it_inData;
				}
				else if(buffer[0] == '('){
					list<string> inData;
					inData = strtoken(buffer);
					newnode.range_index_a.clear();
					newnode.range_index_b.clear();
	
					list<string>::iterator it_inData = inData.begin();
					list<string>::iterator it2_inData = inData.begin();
					++it2_inData;
		
					for(int i = 0 ; i < range_size - 1 ;++it_inData,++it2_inData, i++){
	
						newnode.range_index_a.push_back(*it_inData);
						newnode.range_index_b.push_back(*it2_inData);
	
						if(i != range_size - 2){
							++it_inData;
							++it2_inData;
						}
					}
					table_index.insert(pair<string,table_data>(newnode.tableName,newnode));
				}
				else{
					list<string> inData;
					inData = strtoken(buffer);
					list<string>::iterator it_inData = inData.begin();
					range_size = inData.size();
	
					newnode.range.clear();
					for(;it_inData != inData.end(); it_inData++){
	
						newnode.range.push_back(stod(*it_inData));
					}
				}	
			}
		}
	}
	infile.close();
}


list<string> strtoken(char str[]) {
	list<string> data;

	const char *d = " ";
	char *strToken;
	char *next_token;
	strToken = strtok_r(str, d, &next_token);
	while (strToken != NULL) {
		string token(strToken);
		data.push_back(token);
		strToken = strtok_r(NULL, d, &next_token);
	}
	return data;
}

string spilt_InputPath(char *fileName){
	string pathName(fileName);
	int lastpos=pathName.size() - 1;
	while(pathName[lastpos]!='/'){
		pathName.pop_back();
		--lastpos;
	}
	for(unsigned int pos = 0;pos < pathName.size();++pos){// change '/' into '//'
		if(pathName[pos] == '/'){
			pathName.insert(pos,"/");
			++pos;
		}
	
	}
	
	return pathName;
}

string spilt_OutputPath(char* fileName){
	
	string pathName(fileName);
	for(int i = 0;i < 3;++i){
		pathName.pop_back();
		int lastpos=pathName.size() - 1;
		while(pathName[lastpos]!='/'){
			pathName.pop_back();
			--lastpos;
		}
	}
	pathName+="output/";
	for(unsigned int pos = 0;pos < pathName.size();++pos){// change '/' into '//'
		if(pathName[pos] == '/'){
			pathName.insert(pos,"/");
			++pos;
		}
	
	}
	return pathName;
	
}
