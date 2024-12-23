#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#define BUFFER_SIZE 1024

// 获取进程名
void GetProcessName(DWORD processID, TCHAR *processName, DWORD size) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess) {
        if (!QueryFullProcessImageName(hProcess, 0, processName, &size)) {
            _tcscpy(processName, TEXT("Unknown"));
        }
        CloseHandle(hProcess);
    } else {
        _tcscpy(processName, TEXT("Unknown"));
    }
}

// 获取进程的运行时间
long GetProcessUptime(HANDLE hProcess) {
    FILETIME createTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(hProcess, &createTime, &exitTime, &kernelTime, &userTime)) {
        // 获取系统当前时间
        FILETIME currentTime;
        GetSystemTimeAsFileTime(&currentTime);

        ULARGE_INTEGER current, start;
        current.LowPart = currentTime.dwLowDateTime;
        current.HighPart = currentTime.dwHighDateTime;

        start.LowPart = createTime.dwLowDateTime;
        start.HighPart = createTime.dwHighDateTime;

        return (long)((current.QuadPart - start.QuadPart) / 10000000); // 转换为秒
    }
    return -1; // 获取失败
}

// 获取进程的内存使用情况
SIZE_T GetProcessMemoryUsage(HANDLE hProcess) {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024; // 转换为 KB
    }
    return 0;
}

// 显示进程信息
void DisplayProcessInfo() {
    DWORD processes[BUFFER_SIZE], count, i;

    // 获取所有进程的 PID
    if (!EnumProcesses(processes, sizeof(processes), &count)) {
        printf("Failed to enumerate processes.\n");
        return;
    }

    count /= sizeof(DWORD); // 计算进程数量

    printf(" %-30s %-15s %-10s\n", "Process Name", "Uptime (s)", "Memory (KB)");
    printf("------------------------------------------------------------------\n");

    // 遍历每个进程
    for (i = 0; i < count; i++) {
        if (processes[i] == 0) continue; // 跳过空进程

        TCHAR processName[MAX_PATH] = TEXT("<Unknown>");
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);

        if (hProcess) {
            // 获取进程名
            GetProcessName(processes[i], processName, MAX_PATH);

            // 获取进程运行时间
            long uptime = GetProcessUptime(hProcess);

            // 获取进程内存使用情况
            SIZE_T memoryUsage = GetProcessMemoryUsage(hProcess);

            // 打印进程信息
            if (uptime != -1) {
                printf(" %-30s %-15ld %-10llu\n", processName, uptime, memoryUsage);
            }

            CloseHandle(hProcess);
        }
    }
}

int main() {
    while (1) {
        system("cls"); // 清屏
        DisplayProcessInfo();
        Sleep(1000); // 每秒刷新一次
    }
    return 0;
}
