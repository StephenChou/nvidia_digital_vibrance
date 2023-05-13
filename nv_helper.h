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

#define CSGO_DVC_LEVEL 75

#define NVAPI_QUERY_INTERFACE "nvapi_QueryInterface"

/* 'magic' addresses for nvapi functions */
#define NVAPI_INITIALIZE_ADDR 0x0150E828
#define NVAPI_UNLOAD_ADDR 0x0D22BDD7E
#define NVAPI_ENUMDISPHANDLE_ADDR 0x9ABDD40D
#define NVAPI_GETDVCINFOEX_ADDR 0x0E45002D
#define NVAPI_SETDVCLEVEL_ADDR 0x172409B4
#define NVAPI_SETDVCLEVELEX_ADDR 0x4A82C2B1
#define NVAPI_GETERROR_ADDR 0x6C2D048C

typedef struct
{
	unsigned int version;
	int currentLevel;
	int minLevel;
	int maxLevel;
	int defaultLevel;

} NV_DISPLAY_DVC_INFO_EX;

/* function pointer hooks to NvAPI dll */
typedef int* (*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int (*NvAPI_Initialize_t)();
typedef int (*NvAPI_Unload_t)();
typedef int (*NvAPI_EnumNvidiaDisplayHandle_t)(int thisEnum, int* pNvDispHandle);
typedef int (*NvAPI_GetDVCInfoEx_t)(int handle, int outputId, NV_DISPLAY_DVC_INFO_EX *dvc_info);
typedef int (*NvAPI_SetDVCLevel_t)(int handle, int outputId, int level);
typedef int(*NvAPI_SetDVCLevelEx_t)(int hNvDisplay, int outputId, NV_DISPLAY_DVC_INFO_EX* pDVCInfo);
typedef int (*NvAPI_GetErrorMessage_t)(_NvAPI_Status nr, char szDesc[64]);


/* struct holding function hooks */
struct nvapi_hooks {
	int NvAPI_handle;
	NvAPI_QueryInterface_t NvAPI_QueryInterface;
	NvAPI_Initialize_t NvAPI_Initialize;
	NvAPI_Unload_t NvAPI_Unload;
	NvAPI_EnumNvidiaDisplayHandle_t NvAPI_EnumNvidiaDisplayHandle;
	NvAPI_GetDVCInfoEx_t NvAPI_GetDVCInfoEx;
	NvAPI_SetDVCLevel_t NvAPI_SetDVCLevel;
	NvAPI_SetDVCLevelEx_t NvAPI_SetDVCLevelEx;
	NvAPI_GetErrorMessage_t NvAPI_GetErrorMessage;
};

extern struct nvapi_hooks* nvapi_hooks;


/* functions */
struct nvapi_hooks* nv_init_lib();
void nv_initialize(struct nvapi_hooks* nvapi_hooks);
void nv_enumerate_displays(struct nvapi_hooks* nvapi_hooks);
NV_DISPLAY_DVC_INFO_EX nv_get_digital_vibrance(struct nvapi_hooks* nvapi_hooks);
void nv_set_digital_vibrance(struct nvapi_hooks* nvapi_hooks, int level);
void nv_set_digital_vibrance_ex(struct nvapi_hooks* nvapi_hooks, int level);
void nv_set_digital_vibrance_default(struct nvapi_hooks* nvapi_hooks);
void nv_exit(struct nvapi_hooks* nvapi_hooks);
void nv_handle_error(struct nvapi_hooks* nvapi_hooks, NvAPI_Status nv_status);




