#include "nv_helper.h"

/* Initialize struct holding function hooks needed to set digital vibrance. This is done by getting the procedure address of
    the Nvidia query interface in order to cast specific NvAPI functions into function pointers stored in the struct.
*/
struct nvapi_hooks* nv_init_lib()
{
    HMODULE hmod;
    struct nvapi_hooks *nvapi_hooks;
    int status;

    NvAPI_QueryInterface_t NvAPI_QueryInterface;

    /* initialize nvapi hook struct */
    nvapi_hooks = (struct nvapi_hooks*)calloc(1, sizeof(struct nvapi_hooks));

    /* calloc error checking */
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

    /* Cast NvAPI functions into function pointers in the struct */
    nvapi_hooks->NvAPI_Initialize = (NvAPI_Initialize_t)(*NvAPI_QueryInterface)(NVAPI_INITIALIZE_ADDR);
    nvapi_hooks->NvAPI_Unload = (NvAPI_Unload_t)(*NvAPI_QueryInterface)(NVAPI_UNLOAD_ADDR);
    nvapi_hooks->NvAPI_SetDVCLevel = (NvAPI_SetDVCLevel_t)(*NvAPI_QueryInterface)(NVAPI_SETDVCLEVEL_ADDR);
    nvapi_hooks->NvAPI_EnumNvidiaDisplayHandle = (NvAPI_EnumNvidiaDisplayHandle_t)(*NvAPI_QueryInterface)(NVAPI_ENUMDISPHANDLE_ADDR);
    nvapi_hooks->NvAPI_GetErrorMessage = (NvAPI_GetErrorMessage_t)(*NvAPI_QueryInterface)(NVAPI_GETERROR_ADDR);


    return nvapi_hooks;
}

/* Call the NvAPI_Initialize function to initialize NvAPI (required call) */
void nv_initialize(struct nvapi_hooks* nvapi_hooks)
{
    NvAPI_Status status;

    status = (NvAPI_Status)nvapi_hooks->NvAPI_Initialize();

    nv_handle_error(nvapi_hooks, status);
}

/* Call the NvAPI_EnumNvidiaDisplayHandle function to get the display handle, which id's each display/monitor connected. */
void nv_enumerate_displays(struct nvapi_hooks* nvapi_hooks)
{
    NvAPI_Status status;

    status = (NvAPI_Status)nvapi_hooks->NvAPI_EnumNvidiaDisplayHandle(0, &(nvapi_hooks->NvAPI_handle));

    nv_handle_error(nvapi_hooks, status);
}

/* Call the NvAPI_SetDVCLevel function to set the digital vibrance of a display. */
void nv_set_digital_vibrance(struct nvapi_hooks* nvapi_hooks, int level)
{

}

/* Handle error checking when making NvAPI calls */
void nv_handle_error(struct nvapi_hooks *nvapi_hooks, NvAPI_Status nv_status)
{

    NvAPI_ShortString sz_desc;

    if (nv_status != NVAPI_OK) {
        nvapi_hooks->NvAPI_GetErrorMessage(nv_status, sz_desc);
        fprintf(stderr, "ERROR: NvAPI returned error: \'%s\', exiting.\n", sz_desc);

        exit(EXIT_FAILURE);
    }

}
