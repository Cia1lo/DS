#include <stdio.h>
#include <windows.h>
#include <Psapi.h>
typedef struct ActiveProcess
{
	char processName[1024];
	int pid;
	long memory;
	int uptime;
	ActiveProcess* next;
};

typedef struct deadProcess
{
	char processName[1024];
	int pid;
	long memory;
	int uptime;
	deadProcess* last;
	deadProcess* next;
};



void GetProcessInfo(int pid)
{
	HANDLE Process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	PROCESS_MEMORY_COUNTERS pmc;


}

int main()
{
	return 0;
}