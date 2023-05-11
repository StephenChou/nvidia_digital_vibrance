#include "check_process.h"

DWORD poll_processes_by_name(char name[MAX_NAME_LENGTH]) 
{
    DWORD procs[1024], cb_needed, c_processes;
    unsigned int i;

    if (!EnumProcesses(procs, sizeof(procs), &cb_needed)) return -1;

    c_processes = cb_needed / sizeof(DWORD);

    for (i = 0; i < c_processes; i++) {
        if (procs[i] != 0) {
            if (check_pid(procs[i], name) == 1) return procs[i];
        }
    }

    return -1;
}

int check_pid(DWORD pid, char name[MAX_NAME_LENGTH])
{
    int ret;

    char sz_process_name[MAX_PATH] = "";

    HANDLE h_process = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, pid);

    /* Check if opening process failed */
    if (h_process == NULL) {
        return -1;
    }

    HMODULE hmod;
    DWORD cb_needed;

    if (EnumProcessModules(h_process, &hmod, sizeof(hmod), &cb_needed))
    {
        GetModuleBaseName(h_process, hmod, sz_process_name,
            sizeof(sz_process_name) / sizeof(char));
    }

    /* if the process name matches the one we're looking for, return success (PID checked is the one we're looking for). */
    if (strncmp(sz_process_name, name, strlen(name)) == 0) {
        ret = 1;
    } else ret = -1;

    CloseHandle(h_process);

    return ret;
}