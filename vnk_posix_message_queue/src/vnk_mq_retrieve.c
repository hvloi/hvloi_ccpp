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

static void show_mq_attr(const char *mq_name, struct mq_attr *attr)
{
    #define OUT stdout

    fprintf(OUT, "\n");
    fprintf(OUT, "  Queue name: [%s]\n", mq_name);

    fprintf(OUT, "  Maximum number of message in queue  : [%ld]\n",
                attr->mq_maxmsg);

    fprintf(OUT, "  Maximum message size                : [%ld]\n",
                attr->mq_msgsize);

    fprintf(OUT, "  Number of message currently in queue: [%ld]\n",
                attr->mq_curmsgs);

    fprintf(OUT, "\n");

    return;
}

/*
 * Function : vnk_mq_retrieve
 * Input    :
 * Output   :
 * NOTE     : retrieve iformation of a POXIS MQ
 */
int vnk_mq_retrieve(const char *mq_name)
{
    mqd_t mq_d;
    struct mq_attr attr;
    bool hasErr = NO;

    // We just reading
    int o_flags = O_RDONLY;


    if(traceIsEnabled)
    {
        vnk_trace_notify("calling open_mq() inside \"%s\"", __FUNCTION__);
    }
    mq_d = mq_open(mq_name, o_flags);
    if(mq_d == (mqd_t) -1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_open() inside \"%s\"", __FUNCTION__);
        goto runrun;
    }

    if (mq_getattr(mq_d, &attr) == -1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_getattr() inside \"%s\"", __FUNCTION__);
        goto runrun;
    }

    // There there what we wanttt
    // vnk_debug_notify("already get into \"%s\"", __FUNCTION__);

    // Calling show MQ informations
    show_mq_attr(mq_name, &attr);

runrun:
    // Clean clean...
    if(mq_d > 0)
    {
        if(traceIsEnabled)
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
