#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>
#include <list> 
#include <iterator>
#include <sstream>
#include <vector>
#include <chrono>
#include <stdio.h>

using namespace std;
double myArray[756][1008];
double mynewArray[756][1008];
double myvalArray[756][1008];

int findcoor(int row, int col){
   return (row*800)+col;
}

int sobel(vector<int> op, int row, int col){
   int counter = 0;
   int sum = 0;
   for(int r = -1;r<=1;r++){
      for(int c = -1;c<=1;c++){
         sum = sum+ (myArray[r+row][c+col]*op[counter]);
         counter+=1;
      }
   }
   return sum;
}
bool is_number(const string& s){
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
vector<int> readFile(string file) {
	ifstream input(file);
   string temp = "";
	vector<int> sizing = {};
	int variables = 0;
	while (variables<3) {
		input>>temp;
		if (is_number(temp)) {
         int intemp = stoi(temp);
			sizing.push_back(intemp);
			variables+=1;
		}
	}
	int three = 0;
	int width = sizing[0];
   int height = sizing[1];
   int maxVal = sizing[2];
   
	int a = 0;
   int b = 0;
   int c = 0;
   for(int i = 0;i<height;i++){
      for(int j = 0;j<width;j++){
         input>> a>>b >>c;
         myArray[i][j] = (a+b+c)/3.0;
      }
      }
      return sizing;
   }

void display(string output,vector<int> v){
	ofstream img(output); 
	img << "P3" << endl;
	img << v[0] << " " << v[1] << endl;
	img << 1 << endl;
   
	for (int y = 0; y < v[1]; y++) {
		for (int x = 0; x < v[0]; x++) {
			img << (int)mynewArray[y][x]<<" "<<(int)mynewArray[y][x]<<" "<< (int)mynewArray[y][x]<<" ";
		}
		img << endl;
	}
}
int main(){
   srand(time(0));
   vector<int> s = readFile("arm.ppm");
     
   
   vector<int> x{ -1, 0, 1 , -2, 0, 2 ,  -1, 0, 1 };
   vector<int> y{ 1, 2, 1, 0, 0, 0, -1, -2, -1 };
   for(int i = 0;i<s[1];i++){
      for(int j = 0; j<s[0];j++){
         mynewArray[i][j] = 0;
      }
      }
   
   for(int i = 0;i<s[1];i++){
      for(int j = 0; j<s[0];j++){
         int a = pow(sobel(x,i,j),2);
         int b = pow(sobel(y,i,j),2);
         int sum = a+b;
         double val = sqrt(sum);
         myvalArray[i][j] = val;
         if(val>90 && val<150)
            mynewArray[i][j] = 1;
    
         
      }
   }
   for(int i = 1;i<s[1]-1;i++){
      for(int j = 1; j<s[0]-1;j++){
         if(mynewArray[i][j] == 1){
            for(int a = -1;a<2;a++){
               for(int b = -1;b<2;b++){
                  if(mynewArray[i+a][j+b]!=1 && (myvalArray[i+a][j+b]>80 && myvalArray[i+a][j+b]<165))
                     mynewArray[i+a][j+b] =1;
               }
            }
         }
      }
   }
      display("armout.ppm",s);
      return 0;
      
}
