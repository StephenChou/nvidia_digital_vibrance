/*

    Main entry point for digital vibrance script. 


*/

#include <stdio.h>
#include <signal.h>

#include "nv_helper.h"
#include "check_process.h"
#include "signal_handler.h"

#define CSGO_PROG_NAME "csgo.exe"

#define MAX_ATTEMPTS 2000

/* global nvapi_hooks struct */
struct nvapi_hooks* nvapi_hooks;

int main(int argc, char* argv[])
{
    int pid, retries, attempts;
    
    NvAPI_Status nv_status;

    pid = -1;
    retries = 0;
    attempts = 0;

    nvapi_hooks = nv_init_lib();
    nv_initialize(nvapi_hooks);

    /* enumerate display handle */
    nv_enumerate_displays(nvapi_hooks);

    /* catch interrupt signals */
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);

    while (attempts < MAX_ATTEMPTS) {

        /* poll all processes to see if program is running */
        pid = poll_processes_by_name(CSGO_PROG_NAME);

        /* if process not running, set to default vibrance level */
        if (pid == -1) {
            printf("Process not running, retrying (%d/%d)\n", attempts++, MAX_ATTEMPTS);
            
            /* set to default level */
            nv_set_digital_vibrance_default(nvapi_hooks);
        }
        /* otherwise, set to specified level */
        else {

            printf("Process is running, total polls: %d\n", attempts);
            nv_set_digital_vibrance_ex(nvapi_hooks, CSGO_DVC_LEVEL);

            attempts = 0;
        }

        Sleep(3000);
    }


    return 0;
}
