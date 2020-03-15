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
 * Common libs including.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>

/**
 * VNK including.
 **/
#include "VNK_uuddsoc.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

/* Buffer Size */
#define BUF_SIZE 10

/* Server Socket Path */
#define SVR_SOCK_PATH "/tmp/vnk_uudsoc_svr"

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

/**
 * In time of bind, clear existed soc path automatically ?
 **/
static bool vnk_clean_soc_path = false;

/**
 * Show welcome message.
 **/
static void vnk_welcome_msg();

/**
 * Show help.
 **/
static void vnk_help();

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/



/**
 * MAIN FUNCTION
 **/
int main(int argc, char *argv[])
{
    /* Variables Declaration */
    int op, exitCode;
    uuddsock_conf_t conf;

    /* Return / Exit Code */
    int R_Code, E_Code;

    /* Welcome Message */
    vnk_welcome_msg();

    R_Code = RETURN_OK;
    E_Code = EXIT_OK;

    if(argc <= 1)
    {
        vnk_error_notify(NO_ERRNO, "Argument is required, type \"%s --help\""
                    " for help.\n", argv[0]);
        goto EndPoint;
    }

    memset(&conf, 0, sizeof(uuddsock_conf_t));

    /* Options Parsing */
    while(RUNNING)
    {
        int option_index = 0;

        static struct option vnk_long_options[] = {
            {"role"   , required_argument, NULL,  'r'},
            {"clear"  , optional_argument, NULL,  'c'},
            {"help"   , no_argument,       NULL,  'h'},
            {NULL     , 0,                 NULL,   0}
        };

        op = getopt_long(argc, argv, "r:ch", vnk_long_options,
                    &option_index);

        if(op == -1)
        {
            break;
        }

        switch (op)
        {
            case 'r':
                if(strncmp(optarg, RSERV_STRING, strlen(optarg)) == 0)
                {
                    conf.role = RSERV;
                }
                else if (strncmp(optarg, RCLIE_STRING, strlen(optarg)) == 0)
                {
                    conf.role = RCLIE;
                }
                else
                {
                    conf.role = RUNDE;
                    vnk_error_notify(NO_ERRNO, "Unknown role \"%s\"", optarg);
                    conf.isValid = false;
                }
                break;

            case 'c':
                vnk_clean_soc_path = true;
                break;

            case 'h':
                vnk_help();
                break;

            case '?':
                vnk_error_notify(NO_ERRNO ,"Un-recorgnized options "
                            "is existed!\n");
                break;

            default:
                break;
        }
    }

    /* Running as Server */
    if(conf.role == RSERV)
    {
        struct sockaddr_un svr_addr, cli_addr;
        int s_fd, j;
        ssize_t numBytes;
        socklen_t len;
        char buf[BUF_SIZE];

        s_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
        if(s_fd == -1)
        {
            vnk_error_notify(errno, "socket(), LINE %d", __LINE__);
            R_Code = errno;
            goto EndPoint;
        }

        /* Construct well-known address and bind server socket to it */
        R_Code = remove(SVR_SOCK_PATH);
        if(R_Code == -1 && errno != ENOENT)
        {
            vnk_error_notify(errno, "remove(), LINE %d", __LINE__);
            R_Code = errno;
            goto EndPoint;
        }
        else
        {
            R_Code = RETURN_OK;
        }

        /* Wiping up the sock addr */
        memset(&svr_addr, 0, sizeof(struct sockaddr_un));
        svr_addr.sun_family = AF_UNIX;

        /**
         * The use of the memset() call in Listing 57-1 ensures that all of the
         * structure fields have the value 0. (The subsequent strncpy() call
         * takes advantage of this by specifying its final argument as one less
         * than the size of the sun_path field, to ensure that this field always
         * has a terminating null byte.)
         **/
        strncpy(svr_addr.sun_path, SVR_SOCK_PATH, sizeof(svr_addr.sun_path)-1);

        /* Binding socket */
        R_Code = bind(s_fd, (struct sockaddr*) &svr_addr,
                    sizeof(struct sockaddr_un));
        if(R_Code == -1)
        {
            vnk_error_notify(errno, "bind(), LINE %d", __LINE__);
            goto EndPoint;
        }
        else
        {
            R_Code = RETURN_OK;
        }

        /**
         * LOOP
         * Receiving message, convert to upper case, send response to the client
         **/
        for(;;)
        {
            len = sizeof(struct sockaddr_un);
            numBytes = recvfrom(s_fd, buf, BUF_SIZE, 0,
                        (struct sockaddr*) &cli_addr, &len);
            if(numBytes == -1)
            {
                vnk_error_notify(errno, "recvfrom(), LINE %d", __LINE__);
                R_Code = RETURN_KO;
                goto EndPoint;
            }

            vnk_info_notify("Server received %ld bytes from %s",
                        (long) numBytes, cli_addr.sun_path);

            /* Convert to upper case */
            for(j = 0; j < numBytes; j++)
            {
                buf[j] = toupper((unsigned char) buf[j]);
            }

            R_Code = sendto(s_fd, buf, numBytes, 0,
                        (struct sockaddr *) &cli_addr, len);
            if(R_Code != numBytes)
            {
                vnk_error_notify(errno, "sendto(), LINE %d", __LINE__);
                goto EndPoint;
            }
            else
            {
                R_Code = RETURN_OK;
            }
        }
    } // Else below

    /* Running as Client */
    else
    if(conf.role == RCLIE)
    {
        /* Client Code */
    }

EndPoint:

    if(R_Code == RETURN_OK)
    {
        E_Code = EXIT_OK;
    }
    else
    {
        E_Code = EXIT_KO;
    }

    vnk_info_notify("All Done! Exiting! Bye!\n");

    exit(E_Code);
}

/**
 * Show welcome message.
 **/
static void vnk_welcome_msg()
{
    printf("\n");
    printf("[ WELCOME TO DGRAM UNIX DOMAIN SOCKET EXAMPLE ]\n");
    printf("  *******************************************  \n\n");

    return;
}

/**
 * Show help.
 **/
static void vnk_help()
{
    return;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
