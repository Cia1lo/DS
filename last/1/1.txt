int getProcessInfo(DWORD pid, char *name, SIZE_T *memory, long *uptime) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (!hProcess) return 0;

    // 获取进程名称
    if (GetModuleBaseName(hProcess, NULL, name, MAX_PROCESS_NAME) == 0) {
        strcpy(name, "Unknown");
    }

    // 获取内存使用
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        *memory = pmc.WorkingSetSize / 1024; // 转换为 KB
    } else {
        *memory = 0;
    }

    // 获取运行时间
    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(hProcess, &creationTime, &exitTime, &kernelTime, &userTime)) {
        FILETIME currentTime;
        GetSystemTimeAsFileTime(&currentTime);

        ULARGE_INTEGER start, current;
        start.LowPart = creationTime.dwLowDateTime;
        start.HighPart = creationTime.dwHighDateTime;

        current.LowPart = currentTime.dwLowDateTime;
        current.HighPart = currentTime.dwHighDateTime;

        *uptime = (long)((current.QuadPart - start.QuadPart) / 10000000); // 转换为秒
    } else {
        *uptime = 0;
    }

    CloseHandle(hProcess);
    return 1;
}