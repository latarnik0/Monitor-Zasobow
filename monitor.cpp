#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <iostream>
#include <cerrno>
#include <ncurses.h>
#include <thread>

using namespace std;

// funkcja zamiany ciągu znaków na int do dalszej manipulacji
int myAtoi(string s){
	int d;
    	int m;
    	int result = 0;
    	std::vector<int> v;
    	for(int i=0;i<s.length();i++){
            	if(int(s[i]) == 48){ d = 0; v.push_back(d); }
            	else if(int(s[i]) == 49){ d = 1; v.push_back(d); }
            	else if(int(s[i]) == 50){ d = 2; v.push_back(d); }
            	else if(int(s[i]) == 51){ d = 3; v.push_back(d); }
            	else if(int(s[i]) == 52){ d = 4; v.push_back(d); }
            	else if(int(s[i]) == 53){ d = 5; v.push_back(d); }
            	else if(int(s[i]) == 54){ d = 6; v.push_back(d); }
            	else if(int(s[i]) == 55){ d = 7; v.push_back(d); }
            	else if(int(s[i]) == 56){ d = 8; v.push_back(d); }
            	else if(int(s[i]) == 57){ d = 9; v.push_back(d); }
            	else if( !v.empty() ){ break; }
            	else{ continue; }
        }

    	for(int i = 0; i<v.size(); i++){
        	m = v[i] * pow(10, v.size() - i - 1);
        	result += m; 
    	}

    	return result;
}

// funkcja do zczytywania danych o RAM
void read_mem(){
	int val;
	string line;
	ifstream infoMem("/proc/meminfo");

	if(!infoMem.is_open()){
		cerr<<"Blad otwarcia pliku"<<endl;
	}

	for(int i=1; i<10; i++){
		getline(infoMem, line);
		val = myAtoi(line);
	       	cout<<line.substr(0, 13)<<" "<<val<<endl;	
	}
}

// funkcja do zczytywania danych statycznych o CPU
void read_cpu(){
	string line;
	int k=0;
	ifstream infoCpu("/proc/cpuinfo");

	if(!infoCpu.is_open()){
		cerr<<"Blad otwarcia pliku"<<endl;
	}
	// do dokończenia
}


// funkcja do zczytywania danych dynamicznych o CPU
void read_cpu_stats(){
	
}


int main(){
	
	read_mem();
	read_cpu();
	
	return 0;
}
