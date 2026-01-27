#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <ncurses.h>
#include <map>
#include <chrono>
#include <thread>


// Struktury danych
struct MEMORY_INFO {
        int tot;
        int av;
};

struct CPU_STATIC_INFO {
        std::string cores;
        std::string vendor;
        std::string cpufamily;
        std::string modelname;
        std::string mhz;
        std::string cachesize;
};

// Główny kontener na dane
struct STATE {
        MEMORY_INFO mem;
        CPU_STATIC_INFO cpus;
};


// Funkcja do zczytywania danych o RAM
void read_mem(STATE &state){

        std::string line;
        std::map<std::string, int> config;
        std::ifstream infoMem("/proc/meminfo");

        if(!infoMem.is_open()){
                std::cerr<<"Blad otwarcia pliku"<<std::endl;
        }

        while(std::getline(infoMem, line)){

                std::stringstream ss(line);
                std::string key;
                int val;
                ss >> key >> val;

                if(!key.empty()){
                        config[key] = val;
                }
        }
        if(config.count("MemTotal:")) { state.mem.tot = config["MemTotal:"]; }
        if(config.count("MemAvailable:")) { state.mem.av = config["MemAvailable:"]; }
}


// funkcja do zczytywania danych statycznych o CPU
void read_cpus(STATE &state){

        std::string line;
        std::map<std::string, std::string> config;
        std::ifstream infoCpu("/proc/cpuinfo");

        if(!infoCpu.is_open()){
                std::cerr<<"Blad otwarcia pliku"<<std::endl;
        }

        while(std::getline(infoCpu, line)){

                std::stringstream ss(line);
                std::string key, val;
                if(!std::getline(ss, key, ':')) continue;

                std::getline(ss, val);

                while(!key.empty() && (key.back() == '\t' || key.back() == ' ')) {
                        key.pop_back();
                }

                size_t first_char = val.find_first_not_of(" \t");

                if(first_char != std::string::npos) {
                        val = val.substr(first_char);
                }
                else{
                        val = "";
                }

                if(!key.empty()){
                        config[key] = val;
                }
			
                if(line.empty() && !config.empty()) break;
        }
	
        if(config.count("cpu cores")) { state.cpus.cores = config["cpu cores"]; }
        if(config.count("vendor_id")) { state.cpus.vendor = config["vendor_id"]; }
        if(config.count("cpu family")) { state.cpus.cpufamily = config["cpu family"]; }
        if(config.count("model name")) { state.cpus.modelname = config["model name"]; }
        if(config.count("cpu MHz")) { state.cpus.mhz = config["cpu MHz"]; }
        if(config.count("cache size")) { state.cpus.cachesize = config["cache size"]; }
}


void print_res(STATE &state){
	int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
	
	for(int i=0; i<186; i++){
		mvprintw(0, i, "_");
    }

    attron(A_REVERSE | A_BOLD);
    mvprintw(1, 85, "MONITOR ZASOBOW");
    attroff(A_REVERSE | A_BOLD);


    for(int i=0; i<186; i++){
		mvprintw(2, i, "_");
    }
	
	for(int i=3; i<46; i++){
		mvprintw(i, 62, "|");
    }

    mvprintw(3, 20, "MEMORY");
	
	for(int i=0; i<62; i++){
		mvprintw(4, i, "_");
	}
	
    mvprintw(5, 0, "Total RAM: %d", state.mem.tot);
    printw(" KB = %.2f MB = %.2f GB", static_cast<float> (state.mem.tot / 1000.0), static_cast<float> (state.mem.tot / 1000000.0));
    mvprintw(6, 0, "Available RAM: %d", state.mem.av);
    printw(" KB = %.2f MB = %.2f GB", static_cast<float> (state.mem.av / 1000.0), static_cast<float> (state.mem.av / 1000000.0));

}


int main(){
	
	initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    char ch = getch();

    while(true){
		char ch = getch();
        if(ch == 'q'){
                break;
        }
        else{
                STATE state;

                read_mem(state);
                read_cpus(state);

                print_res(state);
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
	}	
	return 0;
}
