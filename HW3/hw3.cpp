#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string.h>

using namespace std;

vector<vector<int>> profitTable;
vector<int> resource;

vector<int> ResourceAllocation(){
	/*for(int i = 0; i < profitTable.size(); i++){
		for(int j = 0; j < profitTable[i].size(); j++){
			cout << profitTable[i][j] << " ";
		}
		cout << endl;
	}cout << "resource :";
	for(int i = 0; i < resource.size(); i++){
		cout << resource[i] << " ";
	}cout << endl;*/

	int Course = profitTable[0].size();
	vector<int> DaysToStudy;
	vector<int> answer;

	answer.resize(resource.size());

	for(int i = 0; i < resource.size(); i++){
		int Resource = resource[i];
		DaysToStudy.clear();
		DaysToStudy.resize(Course);
		for(int i = 0; i < Course; i++){
			DaysToStudy[i] = 0;
		}
		for(int j = 0; j < Resource - Course; j++){
			int max = 0;
			int tag;
			for(int k = 0; k < Course; k++){
				int dif;
				if(DaysToStudy[k] == profitTable.size()-1){
					dif = 0;
				}
				else{
					dif = profitTable[DaysToStudy[k]+1][k] - profitTable[DaysToStudy[k]][k];
				}
				if(dif > max){
					max = dif;
					tag = k;
				}
			}
			DaysToStudy[tag]++;
		}

		int tempAns = 0;
		for(int j = 0; j < Course; j++){
			tempAns += profitTable[DaysToStudy[j]][j];
		}
		answer[i] = tempAns;
		//cout << answer[i] << endl;
	}

	profitTable.clear();
	resource.clear();

	return answer;
}

int main(){
	string s;
	string middleTemp;
	stringstream ss;
	bool critical = false;
	int testcase = 0;
	bool adjust = false;
	ifstream fp("input.txt");
	ofstream ofp("output.txt");

	while(getline(fp, s)){
		int temp;
		vector<int> tempRow;

		if(testcase != 0 && adjust == false){
			ss << middleTemp;
			while(ss >> temp){
				tempRow.push_back(temp);
			}
			profitTable.push_back(tempRow);
			tempRow.clear();
			ss.str("");
			ss.clear();
			adjust = true;
		}

		if(!strcmp(s.c_str(), ""))
			continue;
		ss << s;
		if(s.find(" ") == -1){
			temp = atoi(s.c_str());
			if(temp != 0)
				resource.push_back(temp);
			critical = true;
		}
		else{
			if(critical == true){
				middleTemp = s;
				vector<int> tempVec = ResourceAllocation();
				for(int k = 0; k < tempVec.size(); k++){
					ofp << tempVec[k];
					ofp << endl;
				}
				critical = false;
				adjust = false;
				testcase++;
			}
			else{
				while(ss >> temp){
					tempRow.push_back(temp);
				}
				profitTable.push_back(tempRow);
				tempRow.clear();
				critical = false;
			}
		}
		ss.str("");
		ss.clear();
		
	}
	vector<int> tempVec2 = ResourceAllocation();
	for(int k = 0; k < tempVec2.size(); k++){
		ofp << tempVec2[k];
		ofp << endl;
	}
}
