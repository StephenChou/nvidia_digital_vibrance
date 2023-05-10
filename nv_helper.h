#pragma once

#include <Windows.h>
#include <stdio.h>

#include "nvapi_defs.h"

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
#define NVAPI_ENUMDISPHANDLE_ADDR 0x9ABDD40D
#define NVAPI_SETDVCLEVEL_ADDR 0x172409B4
#define NVAPI_GETERROR_ADDR 0x6C2D048C


/* function pointer hooks to NvAPI dll */
typedef int* (*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int (*NvAPI_Initialize_t)();
typedef int (*NvAPI_Unload_t)();
typedef int (*NvAPI_EnumNvidiaDisplayHandle_t)(int thisEnum, int* pNvDispHandle);
typedef int (*NvAPI_SetDVCLevel_t)(int handle, int outputId, int level);
typedef int (*NvAPI_GetErrorMessage_t)(_NvAPI_Status nr, char szDesc[64]);

/* struct holding function hooks */
struct nvapi_hooks {
	int NvAPI_handle;
	NvAPI_QueryInterface_t NvAPI_QueryInterface;
	NvAPI_Initialize_t NvAPI_Initialize;
	NvAPI_Unload_t NvAPI_Unload;
	NvAPI_EnumNvidiaDisplayHandle_t NvAPI_EnumNvidiaDisplayHandle;
	NvAPI_SetDVCLevel_t NvAPI_SetDVCLevel;
	NvAPI_GetErrorMessage_t NvAPI_GetErrorMessage;
};

/* functions */
struct nvapi_hooks* nv_init_lib();
void nv_initialize(struct nvapi_hooks* nvapi_hooks);
void nv_handle_error(struct nvapi_hooks* nvapi_hooks, NvAPI_Status nv_status);
void nv_enumerate_displays(struct nvapi_hooks* nvapi_hooks);
void nv_set_digital_vibrance(struct nvapi_hooks* nvapi_hooks, int level);

