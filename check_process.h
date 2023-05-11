#pragma once
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#define MAX_NAME_LENGTH 64

DWORD poll_processes_by_name(char name[MAX_NAME_LENGTH]);

int check_pid(DWORD pid, char name[MAX_NAME_LENGTH]);