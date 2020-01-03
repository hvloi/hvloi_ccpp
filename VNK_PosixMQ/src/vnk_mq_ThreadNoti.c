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
#include <pthread.h>
#include <mqueue.h>
#include <fcntl.h>
#include <signal.h>

/**
 * Local includes
 **/
#include "vnk_mq_ThreadNoti.h"
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
 * Templates
 **/
static void ThreadFunction();
static void NotifySetup(mqd_t *r_mqd);

/**
 * FUNCTION    :
 * VNK_ThreadNotification
 *
 * SCOPE       :
 * Global
 *
 * DESCRIPTION :
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * c_vnkmq_config: c means copy, passing copy of struct to fucntion.
 *
 **/
int VNK_ThreadNotification(struct vnkmq_config c_vnkmq_config)
{
    int RetCode = 0;
    mqd_t mqd;

    mqd = mq_open(c_vnkmq_config.mq_name, O_RDONLY | O_NONBLOCK);
    if (mqd == (mqd_t) -1)
    {
        RetCode = errno;
        vnk_error_notify(errno, "mq_getattr(), inside %s()", __FUNCTION__);
        goto ExitEntry;
    }

    vnk_info_notify("%s is listenning for comming message,...", IAM);

    NotifySetup(&mqd);

    pause();

ExitEntry:
    return RetCode;
}

/**
 * FUNCTION    :
 * ThreadFunction
 *
 * SCOPE       :
 * Local
 *
 * DESCRIPTION :
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 *
 **/
static void ThreadFunction(union sigval sv)
{
    ssize_t NumRead;
    mqd_t *p_mqd;
    void *buffer;
    struct mq_attr attr;

    p_mqd = sv.sival_ptr;

    if (mq_getattr(*p_mqd, &attr) == -1)
    {
        vnk_error_notify(errno, "mq_getattr(), inside %s()", __FUNCTION__);
        return;
    }

    buffer = malloc(attr.mq_msgsize);
    if (buffer == NULL)
    {
        vnk_error_notify(NO_ERRNO, "malloc(), inside %s()", __FUNCTION__);
        return;
    }

    NotifySetup(p_mqd);

    while ((NumRead = mq_receive(*p_mqd, buffer, attr.mq_msgsize, NULL)) >= 0)
    {
        vnk_info_notify("read %ld bytes!", (long) NumRead);
    }

    if (errno != EAGAIN)
    {
        vnk_error_notify(errno, "mq_receive(), inside %s()", __FUNCTION__);
        return;
    }

    free(buffer);
    pthread_exit(NULL);

    return;
}

/**
 * FUNCTION    :
 * NotifySetup
 *
 * SCOPE       :
 * Local
 *
 * DESCRIPTION :
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 *
 **/
static void NotifySetup(mqd_t *r_mqd)
{
    struct sigevent SEv;

    SEv.sigev_notify = SIGEV_THREAD;
    SEv.sigev_notify_function = ThreadFunction;
    SEv.sigev_notify_attributes = NULL;
    SEv.sigev_value.sival_ptr = r_mqd;

    if (mq_notify(*r_mqd, &SEv) == -1)
    {
        vnk_error_notify(errno, "mq_notify() inside %s", __FUNCTION__);
        return;
    }

    return;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
