#pragma once
#include "structs.hpp" 

void read_mem(STATE &state);
void read_cpus(STATE &state);
void read_cpud(STATE &state);
void read_uptime(STATE &state);
void read_procs(STATE &state);
void count_active_ps(STATE &state);
void read_network(STATE &state);
void read_sysinfo(STATE &state);
bool is_number(const std::string& s);
