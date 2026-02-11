#pragma once
#include <string>
#include <vector>

// Tutaj wklejamy wszystkie Twoje structy
struct MEMORY_INFO {
	int tot;
	int av;
	int usg;
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

struct DISK_INFO {
	// TODO
};

// GŁÓWNA STRUKTURA
struct STATE {
	MEMORY_INFO mem;
	CPU_STATIC_INFO cpus;
	CPU_DYNAMIC_INFO prev;
	CPU_DYNAMIC_INFO curr;
	PROCESS_INFO proc;
	DISK_INFO disk;
	PSAUX psaux;
	NETWORK net;
};
