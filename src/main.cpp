#include <ncurses.h>
#include <thread>
#include <chrono>
#include "structs.hpp"
#include "lime_core.hpp"
#include "ui.hpp"

int main(){
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);
	
	STATE state;
	timeout(500);

	while(true){
		read_procs(state);
		read_uptime(state);
		read_mem(state);
		read_cpus(state);
		read_cpud(state);
		count_active_ps(state);
		read_network(state);
			
		print_res(state);
		refresh();
		
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

		int quit = getch();
		if(quit == 'q' || quit == 'Q'){
			break;
		}
	}
	endwin();
	return 0;
}
