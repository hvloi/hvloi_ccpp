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
 * Global includes
 **/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

/**
 * VNK includes
 **/
#include "VNK_CGO_Utils.h"

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
 * FUNCTION    :
 * VNK_GetOptions
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
 *
 **/
int VNK_GetOptions(int argc, char *argv[])
{
    int RetCode, tmp_code;
    int option_index, this_option_optind, digit_optind;

    RetCode = RETURN_SUCCESS;
    digit_optind = 0;

    vnk_debug_notify("Debug %s()", __FUNCTION__);

    while(RUN)
    {
        this_option_optind = optind ? optind : 1;
        option_index = 0;

        static struct option VNK_LongOptions[] = {
            {"add"    , optional_argument, NULL,  'a'},
            {"append" , no_argument,       NULL,  'p'},
            {"delete" , optional_argument, NULL,  'd'},
            {"verbose", no_argument,       NULL,  'v'},
            {"create" , optional_argument, NULL,  'c'},
            {"file"   , optional_argument, NULL,  'f'},
            {NULL,      0,                 NULL,   0}
        };

        tmp_code = getopt_long(argc, argv, "a::pd::vc::f::012", VNK_LongOptions,
                    &option_index);
        if(tmp_code == -1)
        {
            break;
        }

        /* Some debug information */
        vnk_debug_notify("option_index = %d", option_index);
        vnk_debug_notify("optind = %d", optind);
        vnk_debug_notify("argc = %d", argc);

        switch(tmp_code)
        {
            /**
             * Why we have case 0 ? This is a featue :D
             * In this use case, case 0 never happen
             * If we type short option, do not expect option_index point to
             * element in VNK_LongOptions.
             **/
            case 0:
                vnk_info_notify("Option %s", 
                            VNK_LongOptions[option_index].name);
                if (optarg)
                {
                    vnk_info_notify("with arg %s", optarg);
                }
                break;
            case 'a':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case 'p':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case 'c':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case 'd':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case 'f':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case 'v':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case '0':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case '1':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case '2':
                vnk_info_notify("take option \"%c\"", tmp_code);
                vnk_info_notify("long option name \"%s\" <= may be wrong!",
                            VNK_LongOptions[option_index].name);
                break;
            case '?':
            default :
                vnk_error_notify(NO_ERRNO, "unexpected option %c", tmp_code);
                break;
        }
    }

EndPoint:
    return RetCode;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
