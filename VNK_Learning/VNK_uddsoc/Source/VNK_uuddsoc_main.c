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

/**
 * VNK including.
 **/
#include "VNK_uuddsoc.h"

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

    /* Welcome Message */
    vnk_welcome_msg();

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


EndPoint:

    vnk_info_notify("All Done! Exiting! Bye!\n");

    exit(EXIT_OK);
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
