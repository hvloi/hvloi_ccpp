/******************************************************************************\
********************************************************************************
**                                                                            **
**                  [ V N K - V I N A  K N O W L E D G E ]                    **
**                                                                            **
**                   SITE  : https://www.vinaknowledge.com                    **
**                   EMAIL : hvloi@vinaknowledge.com                          **
**                                                                            **
**                       TAN BINH DST, HCMC, VIET NAM                         **
**                                                                            **
**                      Copyright © 2019 Vina Knowledge                       **
**                                                                            **
********************************************************************************
\******************************************************************************/

/******************************************************************************\
*******************************I*N*C*L*U*D*E*S**********************************
\******************************************************************************/

/**
 * Global includes
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <time.h>

/**
 * "local" includes
 **/
#include "vnk_mq_poxis.h"
#include "vnk_notify.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

bool traceIsEnabled = NO;

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

/**
 * NOTICE:
 * Compile with -lrt option
 **/

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

/**
 * Function: 
 **/
static void bye();
static void looploop();

static void bye()
{
    char s_time[64];
    time_t l_time; // DO NOT use "time" as name of variable, use l_time instead
    struct tm l_tm;
    
    l_time = time(NULL);
    l_tm = *localtime(&l_time);

    sprintf(s_time, "%d-%d-%d %d:%d:%d", l_tm.tm_year + 1900, l_tm.tm_mon + 1,
                        l_tm.tm_mday, l_tm.tm_hour, l_tm.tm_min, l_tm.tm_sec);

    vnk_info_notify("all done, end at %s", s_time);

    return;
}

int main(int argc, char *argv[])
{
    bool hasErr = NO;
    struct mq_attr l_attr;
    struct vnkmq_config l_config;

    memset(&l_config, 0, (size_t)sizeof(struct vnkmq_config));

    if(argc <= 1)
    {
        usageError(argv[0]);
        hasErr = YES;
        goto bye_bye;
    }

    // Get options //
    if(opt_parsing(argc, argv, &l_attr, &l_config))
    {
        hasErr = YES;
        goto bye_bye;
    }

    // DBG //
    // vnk_debug_notify("in \"%s\" l_attr.mq_msgsize=%d", __FUNCTION__,
    //             l_attr.mq_msgsize);

    // Check if TRACE is enabled //
    if(traceIsEnabled)
    {
        vnk_trace_notify("notify TRACE is enabled");
    }

    // Process option //
    if(l_config.action == ACTION_CREATE)
    {
        if(traceIsEnabled)
            vnk_trace_notify("vnk_mq_create()");

        if(vnk_mq_create(&l_config, &l_attr) == RETURN_FAILURE)
        {
            hasErr = YES;
            goto bye_bye;
        }
    }
    else if (l_config.action == ACTION_OPEN)
    {
        if(traceIsEnabled)
        {
            vnk_trace_notify("action OPEN...");
        }
        // Something here,... //
        if(vnk_mq_retrieve(l_config.mq_name) == RETURN_FAILURE)
        {
            hasErr = YES;
            goto bye_bye;
        }
    }
    else if (l_config.action == ACTION_UNLINK)
    {
        // Do something,... //
        if(vnk_mq_unlink(l_config.mq_name) == RETURN_FAILURE)
        {
            hasErr = YES;
            goto bye_bye;
        }
    }
    else if (l_config.action == ACTION_EDIT)
    {
        if (vnk_mq_edit(l_config.mq_name) == RETURN_FAILURE)
        {
            hasErr = YES;
            goto bye_bye;
        }
    }
    else if (l_config.action == ACTION_SEND)
    {
        if (vnk_mq_send (l_config.mq_name, l_config.mq_message)
                                                            == RETURN_FAILURE)
        {
            hasErr = YES;
            goto bye_bye;
        }
    }

    else if (l_config.action == ACTION_RECIEVE)
    {
        if (vnk_mq_recieve(l_config.mq_name) == RETURN_FAILURE)
        {
            hasErr = YES;
            goto bye_bye;
        }
    }

    // Debug //
    // vnk_debug_notify("in \"%s\", l_config.mq_oflag = %d", __FUNCTION__,
    //             l_config.mq_oflag);

bye_bye:

    // Clean up before leave //
    if(l_config.mq_d > 0)
    {
        if(mq_close(l_config.mq_d) < 0)
        {
            vnk_error_notify(errno, "mq_close()");
            hasErr = YES;
        }
        else
        {
            if(traceIsEnabled)
            {
                vnk_trace_notify("closed descriptor of %s", l_config.mq_name);
            }
        }
    }

    if(hasErr)
    {
        exit(EXIT_FAILURE);
    }

    // Bye bye if no error, otherwise show error and stop //
    bye();

    exit(EXIT_SUCCESS);
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
