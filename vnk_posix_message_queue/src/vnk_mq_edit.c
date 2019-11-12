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



/*******************************************************************************
 *********************************INCLUDES**************************************
 ******************************************************************************/

#include <stdio.h>
#include <mqueue.h>

#include "vnk_mq_poxis.h"
#include "vnk_notify.h"

/*******************************************************************************
 **********************************GLOBAL***************************************
 ******************************************************************************/


/*******************************************************************************
 **********************************PRIVATE**************************************
 ******************************************************************************/

/*
 * Function : vnk_mq_edit
 * Input    :
 * Output   :
 * NOTE     : edit attribute of a POXIS MQ, this does not really work,
 * O_NONBLOCK is not "saved", it only has affect following the mq_open().
 * After mq_close(), it is gone.
 */
int vnk_mq_edit(const char *mq_name)
{
    mqd_t mq_d;
    int o_flags;
    struct mq_attr attr;
    bool hasErr = NO;

    /*O_NONBLOCK: causes the queue to be opened in non-blocking mode.If a 
    subsequent call to mq_receive() or mq_send() can’t be performed without
    blocking, the call will fail immediately with the error EAGAIN.*/
    o_flags = O_RDWR | O_NONBLOCK;

    mq_d = mq_open(mq_name, o_flags);
    if(mq_d == (mqd_t)-1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_open() in \"%s\"", __FUNCTION__);
        goto gogo;
    }

    // Get old configuration
    if (mq_getattr(mq_d, &attr) == -1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_getattr() inside \"%s\"", __FUNCTION__);
        goto gogo;
    }

    // Change configuration
    if (attr.mq_flags & O_NONBLOCK)
    {
        if (traceIsEnabled)
        {
            vnk_trace_notify("O_NONBLOCK is set, clear it");
        }
        attr.mq_flags &= ~O_NONBLOCK;
    }
    else
    {
        if (traceIsEnabled)
        {
            vnk_trace_notify("O_NONBLOCK is NOT set, set it");
        }
        attr.mq_flags |= O_NONBLOCK;
    }

    // Save configuration
    if (mq_setattr(mq_d, &attr, NULL) == -1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_setattr() in \"%s\"", __FUNCTION__);
        goto gogo;
    }

gogo:
    // Clean up
    if(mq_d > (mqd_t)0)
    {
        if (traceIsEnabled)
        {
            vnk_trace_notify("calling mq_close() inside \"%s\"", __FUNCTION__);
        }
        if(mq_close(mq_d) < 0)
        {
            vnk_error_notify(errno, "mq_close() inside \"%s\"", __FUNCTION__);
            hasErr = YES;
        }
    }

    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}
