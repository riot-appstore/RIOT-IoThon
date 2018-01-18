/*
 * Copyright (C) 2017 RAPStore
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */


#ifndef PCMBOX_H
#define PCMBOX_H

#include "list.h"
#include "mbox.h"


#ifdef __cplusplus
extern "C" {
#endif

struct pcmbox_prod_t {
    mbox_t *mbox;
    unsigned num_consummers;
    list_node_t consummers;
};


struct pcmbox_event_t {
    event_t super;
    msg_t *msg;
    void *arg;
};

enum pcmbox_cons_type_t {
    MBOX_CONSUMER,
    EVENT_CONSUMER,
};


struct pcmbox_cons_t {
    list_node_t next;
    int type;
    union {
        struct {
            event_handler_t handler;
            void *arg;
            struct pcmbox_event_t *ebox;
        } event;
        struct {
            mbox_t *mbox;
        } mbox;
    };
};


void pcmbox_init_global(void);


void pcmbox_init(struct pcmbox *pcmbox, msg_t *queue, unsigned int queue_size);


/*
 * Sends message to all listeners. If no listeners discard message.
 */
void pcmbox_dispatch(struct pcmbox *pcmbox, msg_t *msg);

/*
 * Try sending message to all listeners. If no listeners discard message.
 * If mailbox is full this function will * return right away.
 */
int pcmbox_try_dispatch(struct pcmbox *pcmbox, msg_t *msg);


int pcmbox_add_listener(struct pcmbox *pcmbox, struct pcmbox_cons_t *cons);




#ifdef __cplusplus
}
#endif
#endif /* PCMBOX_H */
