#include "nv_helper.h"

struct nvapi_hooks* nv_init_lib()
{
    HMODULE hmod;
    struct nvapi_hooks *nvapi_hooks;
    NvAPI_QueryInterface_t NvAPI_QueryInterface;

    nvapi_hooks = (struct nvapi_hooks*)calloc(1, sizeof(struct nvapi_hooks));

    if (nvapi_hooks == NULL) {
        fprintf(stderr, "ERROR: Could not allocate memory for nvapi hook struct. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    /* load nvapi dll */    
    hmod = LoadLibraryA(NVAPI_DLL);

    /* check if loaded successfully */
    if (hmod == NULL) {
        fprintf(stderr, "ERROR: Could not load: %s, exiting.\n", NVAPI_DLL);
        exit(EXIT_FAILURE);
    }
    
    /* hook nvapi_queryinterface from dll */
    nvapi_hooks->NvAPI_QueryInterface = (NvAPI_QueryInterface_t) GetProcAddress(hmod, NVAPI_QUERY_INTERFACE);

    /* store in local variable for ease with casting */
    NvAPI_QueryInterface = nvapi_hooks->NvAPI_QueryInterface;

    nvapi_hooks->NvAPI_Initialize = (NvAPI_Initialize_t)(*NvAPI_QueryInterface)(NVAPI_INITIALIZE_ADDR);
    nvapi_hooks->NvAPI_Unload = (NvAPI_Unload_t)(*NvAPI_QueryInterface)(NVAPI_UNLOAD_ADDR);

    return nvapi_hooks;
}

