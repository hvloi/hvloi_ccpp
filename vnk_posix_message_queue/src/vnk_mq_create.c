/*******************************************************************************
 *
 *      VINA KNOWLEDGE
 *
 *      Site : https://www.vinaknowledge.com
 *      Email: hvloi@vinaknowledge.com
 *
 *      Copyright © 2019 Vina Knowledge
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>

#include "vnk_mq_poxis.h"
#include "vnk_notify.h"


/*
 * Some description...
 * After create, look at /dev/mqueue/ to find queue
 */
int vnk_mq_create(struct vnkmq_config *l_vnkmq_config)
{
    bool hasErr = NO; // init
    mqd_t mqd;

    mqd = mq_open(l_vnkmq_config->q_name, O_RDWR | O_CREAT | O_EXCL, S_IRWXU |
                    S_IRWXG, NULL);

    if(mqd == (mqd_t)-1)
    {
        vnk_error_notify(errno, "mq_open()");
        hasErr = YES;
        goto byee;
    }

    // Created successfully
    l_vnkmq_config->mq_d = mqd;

byee:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

