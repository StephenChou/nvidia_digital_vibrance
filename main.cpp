#include <stdio.h>
#include "nv_helper.h"

int main(int argc, char* argv[])
{

    struct nvapi_hooks* nvapi_hooks;
    NvAPI_Status nv_status;

    nvapi_hooks = nv_init_lib();
    
    nv_initialize(nvapi_hooks);

    /* enumerate display handle */
    nv_enumerate_displays(nvapi_hooks);

    return 0;
}
