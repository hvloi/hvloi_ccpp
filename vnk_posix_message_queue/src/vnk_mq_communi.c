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
 * I N T E R N A L
 * Function: vnk_mq_show_message
 * Input   :
 * Output  :
 * NOTE    : Used to show MQ message
 */
static int vnk_mq_show_message(char *message, ssize_t *size)
{
    #define OUT stdout

    bool hasErr = NO;

    fprintf(OUT, "\n");
    fprintf(OUT, "[MESSAGE]: ");
    fprintf(OUT, "%s\n", message);

    // N E E D A N A T T E N T I O N
    // Which is better ? Directly write() or fprintf() ?
    // if (write(STDOUT_FILENO, message, *size) == -1)
    // {
    //     hasErr = YES;
    //     vnk_error_notify(NO_ERRNO, "write() inside \"%s\"", __FUNCTION__);
    //     goto dada;
    // }
    // f l u s h i n g
    // write(STDOUT_FILENO, "\n", 1);

dada:
    if (hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}


/*
 * Function: vnk_mq_send
 * Input   :
 * Output  :
 * NOTE    : 
 */
int vnk_mq_send (const char *mq_name, const char *message)
{
    bool hasErr = NO;
    mqd_t mq_d;
    int o_flags;

    o_flags = O_WRONLY | O_NONBLOCK;

    if (traceIsEnabled)
    {
        vnk_trace_notify("calling mq_open() inside \"s\"", __FUNCTION__);
    }
    mq_d = mq_open(mq_name, o_flags);
    if (mq_d == (mqd_t)-1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_open() inside \"%s\"", __FUNCTION__);
        goto endgame;
    }

    if (traceIsEnabled)
    {
        vnk_trace_notify("calling mq_send() inside \"s\"", __FUNCTION__);
    }
    if (mq_send(mq_d, message, strlen(message), 0) == -1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_send() in fucntion \"%s\"", __FUNCTION__);
        goto endgame;
    }

endgame:
    // Clean up first
    if (mq_d > 0)
    {
        if (mq_close(mq_d) < 0)
        {
            vnk_error_notify(errno, "mq_close() inside \"%s\"", __FUNCTION__);
            hasErr = YES;
        }
    }

    if (hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

/*
 * Function: vnk_mq_recieve
 * Input   :
 * Output  :
 * NOTE    : 
 */
int vnk_mq_recieve (const char *mq_name)
{
    bool hasErr = NO;
    mqd_t mq_d;
    struct mq_attr attr;
    int o_flags;
    void *buff;
    ssize_t num_read;

    o_flags = O_RDONLY | O_NONBLOCK;

    mq_d = mq_open(mq_name, o_flags);
    if (mq_d == (mqd_t)-1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_open() in \"%s\"", __FUNCTION__);
        goto dada;
    }

    if (mq_getattr(mq_d, &attr) == -1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_getattr() inside \"%s\"", __FUNCTION__);
        goto dada;
    }

    buff = malloc(attr.mq_msgsize);
    if (buff == NULL)
    {
        vnk_error_notify(NO_ERRNO, "malloc() inside \"%s\"", __FUNCTION__);
    }

    num_read = mq_receive(mq_d, buff, attr.mq_msgsize, 0);
    if (num_read == (ssize_t)-1)
    {
        hasErr = YES;
        vnk_error_notify(errno, "mq_receive() inside \"%s\"", __FUNCTION__);
        goto dada;
    }

    // S h o w o u t m e s s a g e
    if (vnk_mq_show_message(buff, &num_read) == RETURN_FAILURE)
    {
        hasErr = YES;
        goto dada;
    }

dada:
    // Clean up . . . 
    if (mq_d > 0)
    {
        if (mq_close(mq_d) < 0)
        {
            hasErr = YES;
            vnk_error_notify(errno, "mq_close() inside \"%s\"", __FUNCTION__);
        }
    }

    if (hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}
