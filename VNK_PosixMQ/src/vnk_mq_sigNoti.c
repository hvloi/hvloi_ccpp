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
 * Standard Libraries.
 **/
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <mqueue.h>

/**
 * Local Headers.
 **/
#include "vnk_mq_sigNoti.h"
#include "vnk_notify.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

/**
 * FUNCTION   :
 * VNK_SigHandler
 *
 * DESCRIPTION:
 * Signal Handler
 *
 * INPUT      :
 *
 * OUTPUT     :
 *
 * NOTE       :
 *
 **/
static void VNK_SigHandler()
{

    return;
}

/**
 * FUNCTION    :
 * VNK_SigReadingMessage
 *
 * DESCRIPTION :
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * r_mqd: r means reference
 *
 **/
static int VNK_SigReadingMessage(sigset_t *r_emptyMask, mqd_t *r_mqd)
{
    // Return code //
    int RetCode = 0;

    struct mq_attr attr;
    void *buffer;
    ssize_t numRead;

    /**
     * Do not intend to validate r_mqd again because it was validated in the time
     * of openning, if there was any error, the program exited at that time.
     **/

    if (mq_getattr(*r_mqd, &attr) == -1)
    {
        vnk_error_notify(NO_ERRNO, "in function %s", __FUNCTION__);
        RetCode = -1;
        goto vnk_black_hole;
    }

    buffer = malloc(attr.mq_msgsize);

    for(;;)
    {
        // Wait for notification signal //
        sigsuspend(r_emptyMask);

        if (mq_notify(mqd, &sev) == -1)
        {
            vnk_error_notify(NO_ERRNO, "in function %s", __FUNCTION__);
            RetCode = -1;
            goto vnk_black_hole;
        }

        while ((numRead = mq_receive(*r_mqd, buffer, attr.mq_msgsize,
                    NULL)) >= 0)
        {
            vnk_info_notify("Read %ld bytes\n", (long) numRead);
        }

        if (errno != EAGAIN)
        {
            vnk_error_notify(errno, "in function %s", __FUNCTION__);
            RetCode = -1;
            goto vnk_black_hole;
        }
    }

vnk_black_hole:
    return RetCode;
}

/**
 * FUNCTION    :
 * VNK_SignalNotification
 *
 * DESCRIPTION :
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * r_mqd: r means reference
 *
 **/
int VNK_SignalNotification(mqd_t *r_mqd)
{
    int RetCode = 0;
    struct sigevent sev;
    sigset_t blockMask, emptyMask;
    struct sigaction sa;

    sigemptyset(&blockMask);
    sigaddset(&blockMask, NOTIFY_SIG);
    if(sigprocmask(SIG_BLOCK, &blockMask, NULL) == -1)
    {
        vnk_error_notify(NO_ERRNO, "sigprocmask inside %s", __FUNCTION__);
        goto VNK_BlHl;
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(NOTIFY_SIG, &sa, NULL) == -1)
    {
        vnk_error_notify(NO_ERRNO, "sigaction inside %s", __FUNCTION__);
        goto VNK_BlHl;
    }

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = NOTIFY_SIG;
    if (mq_notify(*r_mqd, &sev) == -1)
    {
        vnk_error_notify(NO_ERRNO, "mq_notify inside %s", __FUNCTION__);
        goto VNK_BlHl;
    }

    // Call function to read message from queue //
    if ((RetCode = VNK_SigReadingMessage(&emptyMask, r_mqd)) != 0)
    {
        goto VNK_BlHl;
    }

VNK_BlHl:
    return RetCode;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
