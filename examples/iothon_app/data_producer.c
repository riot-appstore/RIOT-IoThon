#include <stdio.h>
#include "xtimer.h"
#include "thread.h"

void *data_producer(void *arg)
{
    (void) arg;

    printf("data_producer started pid: %" PRIkernel_pid "\n", thread_getpid());

    while (1) {
	printf("data producer woke up\n");
        xtimer_sleep(1);
    }

    return NULL;
}
