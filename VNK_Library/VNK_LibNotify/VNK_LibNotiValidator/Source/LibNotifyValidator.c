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
#include <stdlib.h>

/**
 * VNK Includes
 **/
#include "LibNotifyValidator.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

/**
 * Show Greeting Message
 **/
static void VNK_Greeting();

/**
 * Show Exiting Message
 **/
static void VNK_Exiting();

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

static void VNK_Greeting()
{
    printf("\n");
    printf("V N K  -  L i b  N o t i  V a l i d a t o r\n");
    printf("-------------------------------------------\n");
    printf("  - Validation 1: vnk_info_notify ()\n");
    printf("  - Validation 2: vnk_error_notify()\n");
    printf("  - Validation 3: vnk_trace_notify()\n");
    printf("  - Validation 4: VNK_TRACE_NOTIFY()\n");
    printf("  - Validation 5: vnk_debug_notify()\n");
    printf("-------------------------------------------\n");

    return;
}

static void VNK_Exiting()
{
    printf("\n");
    printf(">> ALL DONE! E X I T I N G . . . ! ! !\n");
    printf("-------------------------------------------\n");

    return;
}

int main(int argc, char *argv[])
{
    VNK_Greeting();

    /* Validate vnk_info_notify() */
    printf("\n");
    printf("%s\n", S_L);
    printf(">>  S T A R T  V A L I D A T I O N  1  <<\n\n");
    VALI_vnk_info_notify();
    printf("\n");
    printf(">> V A L I D A T I O N  1  I S  D O N E ! <<\n");
    printf("%s\n\n\n\n", S_L);

    /* Validate vnk_error_notify() */
    printf("\n");
    printf("%s\n", S_L);
    printf(">>  S T A R T  V A L I D A T I O N  2  <<\n\n");
    VALI_vnk_error_notify();
    printf("\n");
    printf(">> V A L I D A T I O N  2  I S  D O N E ! <<\n");
    printf("%s\n\n\n\n", S_L);

    /* Validate vnk_trace_notify() */
    printf("\n");
    printf("%s\n", S_L);
    printf(">>  S T A R T  V A L I D A T I O N  3  <<\n\n");
    VALI_vnk_trace_notify();
    printf("\n");
    printf(">> V A L I D A T I O N  3  I S  D O N E ! <<\n");
    printf("%s\n\n\n\n", S_L);

    /* Validate VALI_VNK_TRACE_NOTIFY() */
    printf("\n");
    printf("%s\n", S_L);
    printf(">>  S T A R T  V A L I D A T I O N  4  <<\n\n");
    VALI_VNK_TRACE_NOTIFY();
    printf("\n");
    printf(">> V A L I D A T I O N  4  I S  D O N E ! <<\n");
    printf("%s\n\n\n\n", S_L);

    /* Validate VALI_vnk_debug_notify() */
    printf("\n");
    printf("%s\n", S_L);
    printf(">>  S T A R T  V A L I D A T I O N  5  <<\n\n");
    VALI_vnk_debug_notify();
    printf("\n");
    printf(">> V A L I D A T I O N  5  I S  D O N E ! <<\n");
    printf("%s\n\n", S_L);

    VNK_Exiting();
    exit(EXIT_SUCCESS);
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
