
#include <stdio.h>
#include "xtimer.h"

#include "thread.h"
void *data_sender(void *arg)
{
    (void) arg;

    printf("data_sender started pid: %" PRIkernel_pid "\n", thread_getpid());

    while (1) {
	printf("data sender woke up\n");
        xtimer_sleep(1);
    }

    return NULL;
}
