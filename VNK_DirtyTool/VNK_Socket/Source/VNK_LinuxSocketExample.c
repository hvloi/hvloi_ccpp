/******************************************************************************\
********************************************************************************
**                                                                            **
**                  [ V N K  -  V I N A  K N O W L E D G E ]                  **
**                                                                            **
**                   SITE  : https://www.vinaknowledge.com                    **
**                   EMAIL : hvloi@vinaknowledge.com                          **
**                                                                            **
**                        TAN BINH DST, HCMC, VIET NAM                        **
**                                                                            **
**                 Copyright © 2019-2020 VNK - Vina Knowledge                 **
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
#include <string.h>
#include <errno.h>

/**
 * V N K - Includes
 **/
#include "VNK_LinuxSocketExample.h"
#include "VNK_VNKSOC_Utilities.h"

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
 * Start Point
 **/
int main(int argc, char *argv[])
{
    /* vnksoc configurations */
    vnksoc_config_t Config;

    /* Socket */
    int SockFD;
    struct sockaddr_un SocAddr;

    int RetCode;

    vnk_info_notify("VNK Socket Exmple Hello World!\n");

    memset(&Config, 0, sizeof(vnksoc_config_t));

    /* Parsing Options */
    RetCode = OptsParsing(argc, argv, &Config);
    if(RetCode != RETURN_SUCCESS)
    {
        vnk_error_notify(NO_ERRNO, "OptsParsing() returned failed code");
        goto EndPoint;
    }

    /* Preparing Socket */
    RetCode = PrepareSocket(&SockFD, &SocAddr);
    if(RetCode != RETURN_SUCCESS)
    {
        vnk_error_notify(NO_ERRNO, "PrepareSocket() returned failed code");
        goto EndPoint;
    }

    /* Seperation of Server and Client */
    if(Config.vnk_soc_role == SERVER)
    {
        bool SocIsExisted;

        /* Server side */
        vnk_info_notify("Server is setting up,...");

        SocIsExisted = SockPathIsExisted(SOC_PATH);
        if(SocIsExisted && !Config.clean_soc_path)
        {
            vnk_info_notify("%s existed! Exiting,...", SOC_PATH);
            RetCode = RETURN_SUCCESS;
            goto EndPoint;
        }

        /* Clean up existed socket path */
        vnk_info_notify("Cleaning up %s,...", SOC_PATH);
        if(remove(SOC_PATH) == -1 && errno != ENOENT)
        {
            vnk_error_notify(errno, "remove()");
            RetCode = RETURN_FAILURE;
            goto EndPoint;
        }
    }
    else
    if(Config.vnk_soc_role == CLIENT)
    {
        /* Client side */
        vnk_info_notify("Client is setting up...");
    }

EndPoint:

    /* Clean up code */

    vnk_info_notify("All Done! Bye!");

    exit(EXIT_SUCCESS);
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
