#include "signal_handler.h"

/* Check if interrupt (Ctrl + c) is signaled */
void sigint_handler(int signal)
{
	if (signal == SIGINT) {
		nv_exit(nvapi_hooks);
		exit(EXIT_SUCCESS);
	}
}

/* Check if program is closed */
void sigterm_handler(int signal)
{
	if (signal == SIGTERM) {
		nv_exit(nvapi_hooks);
		exit(EXIT_SUCCESS);
	}
}