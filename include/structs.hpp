#pragma once
#include <string>
#include <vector>

struct MEMORY_INFO {
	int tot;
	int av;
	int usg;
	int swapt;
	int swapf;
	int swapusg;
};

struct CPU_STATIC_INFO {
	std::string cores;
	std::string vendor;
	std::string cpufamily;
	std::string modelname;
	std::string mhz;
	std::string cachesize;
};

struct CPU_DYNAMIC_INFO {
	long user, nice, system, idle;
    	long iowait, irq, softirq;
	float usage;
	int usageInt;
};

struct PROCESS_INFO {
	int interr;
   	int contextSwitches;
	int bootTime;
    	int allProcs;
    	int runningProcs;
    	int blockedProcs;
	long uptimeRaw;
	int uptimeH, uptimeM, uptimeS;
};

struct PSAUX {
	int kthrd;
	int uthrd;
	std::string paththrd;
};

struct NETWORK {
	unsigned long tx;
	unsigned long rx;
};

struct SYSINFO {
	std::string os;
	std::string kver;
	std::string hostname;
}; 

struct DISK_INFO {
	// TODO
};


// MAIN STRUCTURE
struct STATE {
	MEMORY_INFO mem;
	CPU_STATIC_INFO cpus;
	CPU_DYNAMIC_INFO prev;
	CPU_DYNAMIC_INFO curr;
	PROCESS_INFO proc;
	DISK_INFO disk;
	PSAUX psaux;
	NETWORK net;
	SYSINFO sys;
};
