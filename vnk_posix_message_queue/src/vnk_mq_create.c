/******************************************************************************\
********************************************************************************
**                                                                            **
**                          VNK - VINA KNOWLEDGE                              **
**                                                                            **
**                   Site : https://www.vinaknowledge.com                     **
**                   Email: hvloi@vinaknowledge.com                           **
**                                                                            **
**                     Copyright © 2019 Vina Knowledge                        **
**                                                                            **
********************************************************************************
\******************************************************************************/

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
 * NOTE for mqd_t:
 * The only stipulation that SUSv3 makes about this data type is that it may not
 * be an array; that is, it is guaranteed to be a type that can be used in an
 * assignment statement or passed by value as a function argument.
 * (On Linux, mqd_t is an int, but, for example, on Solaris it is defined as
 * void *.)
 */
int vnk_mq_create(struct vnkmq_config *l_vnkmq_config,
            struct mq_attr *l_mq_attr)
{
    /*
     * Need help to show valid values of mq_attr in case of error
     */

    bool hasErr = NO; // init
    mqd_t mqd;

    mqd = mq_open(l_vnkmq_config->mq_name, l_vnkmq_config->mq_oflag,
            l_vnkmq_config->mq_mode, l_mq_attr);

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

