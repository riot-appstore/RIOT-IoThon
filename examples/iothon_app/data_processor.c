#include <stdio.h>
#include "xtimer.h"
#include "thread.h"

void *data_processor(void *arg)
{
    (void) arg;

    printf("data_processor started pid: %" PRIkernel_pid "\n", thread_getpid());

    while (1) {
	printf("data processor woke up\n");
        xtimer_sleep(1);
    }

    return NULL;
}
