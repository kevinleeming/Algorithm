#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>
#define NONEXISTELEMENT -10000000

using namespace std;

typedef struct YoungTableaus{
	int method;
	int MinNum; // the minimal number in Table
	vector<int> KeyNumber; // Inserted numbers array
	vector<vector<int>> Table;
}YoungTable;

int main(){
	vector<YoungTable> youngTable;
	int TableNum;
	ifstream fp("input.txt");

	char c;
	string ss, temps;
	int temp;
	vector<int> tempRow;

	fp >> TableNum;
	youngTable.resize(TableNum);
	for(int i = 0; i < TableNum; i++){
		fp >> youngTable[i].method;
		getline(fp, ss); // '\n' left in the buffer
		stringstream sss;
		if(youngTable[i].method == 1){
			getline(fp, ss);
			sss << ss;
			while(sss >> temp){
				youngTable[i].KeyNumber.push_back(temp);
			}
		}

		sss.str("");
		sss.clear();
		while(1){
			tempRow.clear();
			getline(fp, ss);
			//cout << ss << endl;
			if(!strcmp(ss.c_str(), "")){
				break;
			}
			sss << ss;
			while(sss >> temps){
				if(!strcmp(temps.c_str(), "x")){
					tempRow.push_back(NONEXISTELEMENT);
				}
				else{
					int con = atoi(temps.c_str());
					tempRow.push_back(con);
				}
			}
			youngTable[i].Table.push_back(tempRow);
			sss.str("");
			sss.clear();
		}
	}

	for(int i = 0; i < TableNum; i++){
		if(youngTable[i].method == 1){ // Insert numbers
			for(int j = 0; j < youngTable[i].KeyNumber.size(); j++){
				int pivotI, pivotJ;
				bool found = false;

				// find empty space to accomodate inserted numbers
				for(int k = 0; k < youngTable[i].Table.size(); k++){
					for(int m = 0; m < youngTable[i].Table[k].size(); m++){
						if(youngTable[i].Table[k][m] == NONEXISTELEMENT){
							youngTable[i].Table[k][m] = youngTable[i].KeyNumber[j];
							found = true;
							pivotI = k;
							pivotJ = m;
							break;
						}
					}
					if(found)
						break;
				}

				// adjust table
				bool up = false, left = false;
				while(1){
					if(pivotJ - 1 >= 0){
						if(youngTable[i].Table[pivotI][pivotJ] >= youngTable[i].Table[pivotI][pivotJ-1]){
							up = true;
						}
						else{
							up = false;
						}
					}
					else{
						up = true;
					}
					if(pivotI - 1 >= 0){
						if(youngTable[i].Table[pivotI][pivotJ] >= youngTable[i].Table[pivotI-1][pivotJ]){
							left = true;
						}
						else{
							left = false;
						}
					}
					else{
						left = true;
					}

					if(up && left)
						break;

					if(up == false && left == true){
						int t = youngTable[i].Table[pivotI][pivotJ];
						youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI][pivotJ-1];
						youngTable[i].Table[pivotI][pivotJ-1] = t;
						pivotJ -= 1;
					}
					else if(up == true && left == false){
						int t = youngTable[i].Table[pivotI][pivotJ];
						youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI-1][pivotJ];
						youngTable[i].Table[pivotI-1][pivotJ] = t;
						pivotI -= 1;
					}
					else if(up == false && left == false){
						int a = abs(youngTable[i].Table[pivotI][pivotJ] - youngTable[i].Table[pivotI][pivotJ-1]);
						int b = abs(youngTable[i].Table[pivotI][pivotJ] - youngTable[i].Table[pivotI-1][pivotJ]);
						if(a > b){
							int t = youngTable[i].Table[pivotI][pivotJ];
							youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI][pivotJ-1];
							youngTable[i].Table[pivotI][pivotJ-1] = t;
							pivotJ -= 1;
						}
						else{
							int t = youngTable[i].Table[pivotI][pivotJ];
							youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI-1][pivotJ];
							youngTable[i].Table[pivotI-1][pivotJ] = t;
							pivotI -= 1;
						}
					}	
				}
			}
		}
		else if(youngTable[i].method == 2){ // Extract min
			youngTable[i].MinNum = youngTable[i].Table[0][0];
			int pivotI = 0, pivotJ = 0;
			bool down = false, right = false;
			while(1){
				if(pivotJ + 1 < youngTable[i].Table[0].size()){
					if(youngTable[i].Table[pivotI][pivotJ+1] == NONEXISTELEMENT){
						right = true;
					}
					else{
						right = false;
					}
				}
				else{
					right = true;
				}
				if(pivotI + 1 < youngTable[i].Table.size()){
					if(youngTable[i].Table[pivotI+1][pivotJ] == NONEXISTELEMENT){
						down = true;
					}
					else{
						down = false;
					}
				}
				else{
					down = true;
				}

				if(down && right)
					break;
				if(down == true && right == false){
					youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI][pivotJ+1];
					youngTable[i].Table[pivotI][pivotJ+1] = NONEXISTELEMENT;
					pivotJ += 1;
				}
				else if(down == false && right == true){
					youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI+1][pivotJ];
					youngTable[i].Table[pivotI+1][pivotJ] = NONEXISTELEMENT;
					pivotI += 1;
				}
				else if(down == false && right == false){
					if(youngTable[i].Table[pivotI+1][pivotJ] >= youngTable[i].Table[pivotI][pivotJ+1]){
						youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI][pivotJ+1];
						youngTable[i].Table[pivotI][pivotJ+1] = NONEXISTELEMENT;
						pivotJ += 1;
					}
					else{
						youngTable[i].Table[pivotI][pivotJ] = youngTable[i].Table[pivotI+1][pivotJ];
						youngTable[i].Table[pivotI+1][pivotJ] = NONEXISTELEMENT;
						pivotI += 1;
					}
				}
			}
		}
		
	}

	/*for(int j = 0; j < TableNum; j++){
		for(int k = 0; k < youngTable[j].Table.size(); k++){
			for(int m = 0; m < youngTable[j].Table[k].size(); m++){
				cout << youngTable[j].Table[k][m] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}*/

	// write into output file
	ofstream fout("output.txt");
	for(int i = 0; i < TableNum; i++){
		// print out method
		if(youngTable[i].method == 1){
			fout << "Insert ";
			for(int j = 0; j < youngTable[i].KeyNumber.size(); j++){
				if(j == youngTable[i].KeyNumber.size()-1){
					fout << youngTable[i].KeyNumber[j] << endl;
				}
				else{
					fout << youngTable[i].KeyNumber[j] << " ";
				}
			}
		}
		else if(youngTable[i].method == 2){
			fout << "Extract-min " << youngTable[i].MinNum << endl;
		}

		// print out adjusted Table
		for(int k = 0; k < youngTable[i].Table.size(); k++){
			for(int m = 0; m < youngTable[i].Table[k].size(); m++){
				if(youngTable[i].Table[k][m] == NONEXISTELEMENT){
					if(m == youngTable[i].Table[k].size()-1)
						fout << "x" << endl;
					else
						fout << "x" << " ";
				}
				else{
					if(m == youngTable[i].Table[k].size()-1)
						fout << youngTable[i].Table[k][m] << endl;
					else
						fout << youngTable[i].Table[k][m] << " ";
				}
			}
		}
		fout << endl;
	}
}