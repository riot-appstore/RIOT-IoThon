/*
 * Copyright (c) 2015-2016 Ken Bannister. All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       gcoap example
 *
 * @author      Ken Bannister <kb2ma@runbox.com>
 *
 * @}
 */

#include <stdio.h>
#include "msg.h"

#include "net/gcoap.h"
#include "kernel_types.h"
#include "shell.h"
#include "thread.h"

#define MAIN_QUEUE_SIZE (4)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int gcoap_cli_cmd(int argc, char **argv);
extern void gcoap_cli_init(void);

extern void *data_processor(void *arg);
extern void *data_producer(void *arg);
extern void *data_sender(void *arg);

char data_processor_stack[THREAD_STACKSIZE_MAIN];
char data_producer_stack[THREAD_STACKSIZE_MAIN];
char data_sender_stack[THREAD_STACKSIZE_MAIN];

static const shell_command_t shell_commands[] = {
    { "coap", "CoAP example", gcoap_cli_cmd },
    { NULL, NULL, NULL }
};

int main(void)
{
    /* for the thread running the shell */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    gcoap_cli_init();
    puts("iothon example app");

    kernel_pid_t proc_pid = thread_create(data_processor_stack, sizeof(data_processor_stack),
                            THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                            data_processor, NULL, "pong");
    
    kernel_pid_t prod_pid = thread_create(data_producer_stack, sizeof(data_producer_stack),
                            THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                            data_producer, NULL, "pong");

    kernel_pid_t send_pid = thread_create(data_sender_stack, sizeof(data_sender_stack),
                            THREAD_PRIORITY_MAIN - 1, THREAD_CREATE_STACKTEST,
                            data_sender, NULL, "pong");
    
   
    (void)proc_pid;
    (void)prod_pid;
    (void)send_pid;
    
    
    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should never be reached */
    return 0;
}
