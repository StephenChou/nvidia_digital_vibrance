#pragma once

#include <Windows.h>
#include <stdio.h>

#include "nvapi_status.h"

/* nvapi dll file for x64 */
#if _WIN64
	#define NVAPI_DLL "nvapi64.dll"
#else
	#define NVAPI_DLL "nvapi.dll"
#endif

#define NVAPI_QUERY_INTERFACE "nvapi_QueryInterface"

/* 'magic' addresses for nvapi functions */
#define NVAPI_INITIALIZE_ADDR 0x0150E828
#define NVAPI_UNLOAD_ADDR 0x0D22BDD7E


/* function pointer hooks to NvAPI dll */
typedef int* (*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int (*NvAPI_Initialize_t)();
typedef int (*NvAPI_Unload_t)();
typedef int (*NvAPI_SetDVCLevel_t)(int handle, int outputId, int level);

/* struct holding function hooks */
struct nvapi_hooks {
	NvAPI_QueryInterface_t NvAPI_QueryInterface;
	NvAPI_Initialize_t NvAPI_Initialize;
	NvAPI_Unload_t NvAPI_Unload;
};

/* functions */
struct nvapi_hooks* nv_init_lib();

