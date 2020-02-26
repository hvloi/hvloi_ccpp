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
#include <unistd.h>

/**
 * V N K - Includes
 **/
#include "VNK_LinuxSocketExample.h"
#include "VNK_VNKSOC_Utilities.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

#define BACKLOG 5

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
    int SockFD, C_SockFD;
    struct sockaddr_un SocAddr;

    ssize_t numRead;

    char buffer[BUF_SIZE];

    int RetCode;
    int ExitCode;

    ExitCode = EXIT_SUCCESS;

    vnk_info_notify("VNK Socket Exmple Hello World!\n");

    memset(&Config, 0, sizeof(vnksoc_config_t));

    /* Parsing Options */
    RetCode = OptsParsing(argc, argv, &Config);
    if(RetCode != RETURN_SUCCESS)
    {
        vnk_error_notify(NO_ERRNO, "OptsParsing() returned failed code!");
        goto EndPoint;
    }

    /* Preparing Socket */
    RetCode = PrepareSocket(&SockFD, &SocAddr);
    if(RetCode != RETURN_SUCCESS)
    {
        vnk_error_notify(NO_ERRNO, "PrepareSocket() returned failed code!");
        goto EndPoint;
    }

    /* Seperation of Server and Client */
    if(Config.vnk_soc_role == SERVER)
    {
        bool SocIsExisted;

        /* Server side */
        vnk_info_notify("Server is setting up,...");

        SocIsExisted = SockPathIsExisted_Stat(SOC_PATH);
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

        /* Binding Socket */
        RetCode = bind(SockFD, (struct sockaddr *) &SocAddr, sizeof(struct sockaddr_un));
        if(RetCode == -1)
        {
            vnk_error_notify(errno, "bind()");
            RetCode = RETURN_FAILURE;
            goto EndPoint;
        }

        RetCode = listen(SockFD, BACKLOG);
        if (RetCode == -1)
        {
            vnk_error_notify(errno, "listen()");
            RetCode = RETURN_FAILURE;
            goto EndPoint;
        }

        /* SERVER Loop */
        for(EVEREVER)
        {
            /* Accepting connection from client */
            C_SockFD = accept(SockFD, NULL, NULL);
            if(C_SockFD == -1)
            {
                vnk_error_notify(errno, "accept()");
                RetCode = RETURN_FAILURE;
                goto EndPoint;
            }

            /* Transfer data from connected socket to stdout until EOF */
            while((numRead = read(C_SockFD, buffer, BUF_SIZE)) > 0)
            {
                if(write(STDOUT_FILENO, buffer, numRead) != numRead)
                {
                    vnk_error_notify(NO_ERRNO, "socket write buffer to STDOUT!");
                    RetCode = RETURN_FAILURE;
                    goto EndPoint;
                }
            }

            /* Read issue */
            if(numRead == -1)
            {
                vnk_error_notify(NO_ERRNO, "socket read buffer from socket!");
                RetCode = RETURN_FAILURE;
                goto EndPoint;
            }

            /* Close socket after reading data */
            if(close(C_SockFD) == -1)
            {
                vnk_error_notify(errno, "close()");
                RetCode = RETURN_FAILURE;
                goto EndPoint;
            }
        }
    }
    else
    if(Config.vnk_soc_role == CLIENT)
    {
        /* Client side */
        vnk_info_notify("Client is setting up...\n");

        /* Connect to server */
        if(connect(SockFD, (struct sockaddr *) &SocAddr,
                    sizeof(struct sockaddr_un)) == -1)
        {
            vnk_error_notify(errno, "connect()");
            RetCode = RETURN_FAILURE;
            goto EndPoint;
        }

        while ((numRead = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0)
        {
            if(write(SockFD, buffer, numRead) != numRead)
            {
                vnk_error_notify(NO_ERRNO, "write()");
                RetCode = RETURN_FAILURE;
                goto EndPoint;
            }
        }

        if(numRead == -1)
        {
            vnk_error_notify(NO_ERRNO, "read()");
            RetCode = RETURN_FAILURE;
            goto EndPoint;
        }
    }

EndPoint:

    /* Clean up code */

    vnk_info_notify("All Done! Bye!");

    /* Seting ExitCode */
    if(RetCode == RETURN_SUCCESS)
    {
        ExitCode = EXIT_SUCCESS;
    }
    else
    {
        ExitCode = EXIT_FAILURE;
    }

    exit(ExitCode);
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
