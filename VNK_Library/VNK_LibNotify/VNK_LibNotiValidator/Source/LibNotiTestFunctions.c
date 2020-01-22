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
 * Global Includes
 **/
#include <stdio.h>

/**
 * V N K - Includes
 **/
#include "LibNotifyValidator.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

/**
 * This defines an example errno.
 * errno value 64 is defined as ENONET with error message:
 * " Machine is not on the network "
 * Please find more information in errno.h
 **/
#define ENOEXAMPLE 64

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
 * Validate vnk_info_notify()
 * XxXxX
 **/
void VALI_vnk_info_notify()
{
    printf(">> Validate vnk_info_notify()\n");

    printf("This is some out put...\n");

    /* Print out some infor message */
    vnk_info_notify("This is an info message");
    vnk_info_notify("This is the second message");
    vnk_info_notify("Infor message with some \\n\n\n");

    printf("This is some other out put...\n");

    printf(">> Validation of vnk_info_notify() is done!\n");

    return;
}

/**
 * Validate vnk_error_notify()
 * XxXxX
 **/
void VALI_vnk_error_notify()
{
    int vnk_errno;

    printf(">> Validate vnk_error_notify()\n");

    printf("This is some out put...\n");

    /* Print out some error message */
    vnk_error_notify(NO_ERRNO,
                "This is an error message");
    vnk_error_notify(NO_ERRNO,
                "This is the second error message");
    vnk_error_notify(NO_ERRNO,
                "Error message with some \\n\n\n");

    /* Set a errno */
    vnk_errno = ENOEXAMPLE;
    vnk_error_notify(vnk_errno,
                "The error message with errno");

    printf("This is some other out put...\n");

    printf(">> Validation of vnk_error_notify() is done!\n");

    return;
}

/**
 * Validate vnk_trace_notify()
 * XxXxX
 **/
void VALI_vnk_trace_notify()
{
    printf(">> Validate vnk_trace_notify()\n");

    printf("This is some out put...\n");

    /* Print out some trace message */
    vnk_trace_notify("This is a trace message");
    vnk_trace_notify("This is the second trace message");
    vnk_trace_notify("Trace message with some \\n \n\n\n");
    vnk_trace_notify("An other trace message");

    printf("This is some other out put...\n");

    printf(">> Validation of vnk_trace_notify() is done!\n");

    return;
}

/**
 * Validate VNK_TRACE_NOTIFY()
 * XxXxX
 **/
void VALI_VNK_TRACE_NOTIFY()
{
    VNK_GlobalTraceIsEnabled = YES;

    printf(">> Validate VNK_TRACE_NOTIFY()\n");

    printf("This is some out put...\n");

    /* Print out some trace message */
    VNK_TRACE_NOTIFY("This is a trace message");
    VNK_TRACE_NOTIFY("This is the second trace message");
    VNK_TRACE_NOTIFY("Trace message with some \\n \n\n\n");
    VNK_TRACE_NOTIFY("An other trace message");

    /* Disable Trace */
    VNK_GlobalTraceIsEnabled = NO;
    printf("Show trace message with VNK_GlobalTraceIsEnabled=NO\n");
    /* Expected behaviour: no message trace is shown */
    VNK_TRACE_NOTIFY("Print trace while trace is disabled");

    printf("This is some other out put...\n\n");

    printf(">> Validation of VNK_TRACE_NOTIFY() is done!\n");

    return;
}

/**
 * Validate vnk_debug_notify()
 * XxXxX
 **/
void VALI_vnk_debug_notify()
{
    printf(">> Validate vnk_debug_notify()\n");

    printf("This is some out put...\n");

    /* Print out some debug message */
    vnk_debug_notify("This is a debug message");
    vnk_debug_notify("This is the second debug message");
    vnk_debug_notify("Debug message with some \\n \n\n\n");
    vnk_debug_notify("An other debug message");

    printf("This is some other out put...\n\n");

    printf(">> Validation of vnk_debug_notify() is done!\n");

    return;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
