#include <stdio.h>
#include "nvapi/nvapi.h"

#define NVAPI_DLL "nvapi64.dll"

typedef int* (*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int (*NvAPI_SetDVCLevel_t)(int handle, int outputId, int level);

void handle_error(NvAPI_Status nv_status)
{

    NvAPI_ShortString sz_desc;
    
    if (nv_status != NVAPI_OK) {
        NvAPI_GetErrorMessage(nv_status, sz_desc);
        fprintf(stderr, "ERROR: NvAPI returned error: \'%s\', exiting.\n", sz_desc);

        exit(EXIT_FAILURE);
    }

}

NvAPI_Status setDVCLevel(NvAPI_SetDVCLevel_t (*NvAPI_SetDVCLevel), int default_handle, int level)
{
    NvAPI_Status status = (NvAPI_Status) (*NvAPI_SetDVCLevel)(default_handle, 0, level);

    handle_error(status);

    return status;
}

int main(int argc, char* argv[])
{

    NvAPI_QueryInterface_t NvAPI_QueryInterface;
    NvAPI_SetDVCLevel_t NvAPI_SetDVCLevel;
    NvAPI_Status nv_status;
    NvDisplayHandle hNvDisplay;
    NvU32 gpu_count;
    NvPhysicalGpuHandle hPhysicalGPU;
    HMODULE hmod;

    hmod = LoadLibraryA(NVAPI_DLL);

    if (hmod == NULL) {
        fprintf(stderr, "ERROR: Could not load: %s, exiting.\n", NVAPI_DLL);
        exit(EXIT_FAILURE);
    }
    
    nv_status = NvAPI_Initialize();

    /* Initialize vars */
    NvAPI_QueryInterface = (NvAPI_QueryInterface_t) GetProcAddress(hmod, "nvapi_QueryInterface");

    NvAPI_SetDVCLevel = (NvAPI_SetDVCLevel_t)(*NvAPI_QueryInterface)(0x172409B4);

    hNvDisplay = NULL;
    gpu_count = 0;
    hPhysicalGPU = NULL;
    
    /* Check if NvAPI initialized */
    handle_error(nv_status);

    /* Enumerate display handle */
    nv_status = NvAPI_EnumNvidiaDisplayHandle(0, &hNvDisplay);
    handle_error(nv_status);

    /* Enumerate physical gpus */
    nv_status = NvAPI_EnumPhysicalGPUs(&hPhysicalGPU, &gpu_count);
    handle_error(nv_status);

    setDVCLevel(&NvAPI_SetDVCLevel, (int)hNvDisplay, 30);

    NvAPI_Unload();

    return 0;
}