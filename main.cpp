#include <stdio.h>
#include <signal.h>
#include "nv_helper.h"
#include "check_process.h"



int main(int argc, char* argv[])
{
    int pid, retries, attempts;
    struct nvapi_hooks* nvapi_hooks;
    NvAPI_Status nv_status;

    pid = -1;
    retries = 0;
    attempts = 0;

    nvapi_hooks = nv_init_lib();
    
    nv_initialize(nvapi_hooks);

    /* enumerate display handle */
    nv_enumerate_displays(nvapi_hooks);

    while (1) {
           
        pid = poll_processes_by_name("csgo.exe");

        /* if process not running, set to default vibrance level */

        if (pid == -1) {
            printf("Process not running, retrying (%d/4), total polls: %d\n", retries, attempts);
            nv_set_digital_vibrance_ex(nvapi_hooks, 50);
        }
        else {
            printf("Process is running, total polls: %d\n", attempts);
            nv_set_digital_vibrance_ex(nvapi_hooks, CSGO_DVC_LEVEL);
        }

        if (attempts++ == 2000) break;

        Sleep(3000);
    }


    return 0;
}
