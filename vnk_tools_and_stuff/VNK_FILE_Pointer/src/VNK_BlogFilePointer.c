/******************************************************************************\
********************************************************************************
**                                                                            **
**                    V N K - V I N A  K N O W L E D G E                      **
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

/*
 * Built includes
 */
#include "VNK_BLogFilePointer.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

#define WC "W E L C O M E  T O  V N K  -  F I L E  P O I N T E R  N O T I C E"

#define ENABLE_NOTIFY_TRACE "YES"

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

static int VNK_Init()
{
    // vnk_debug_notify("inside %s line %d", __FUNCTION__, __LINE__);

    // Enable / Disable Notify Trace
    if(strncmp(ENABLE_NOTIFY_TRACE, "YES", strlen("YES")) == 0)
    {
        // vnk_debug_notify("inside %s line %d", __FUNCTION__, __LINE__);
        VNK_GlobalTraceIsEnabled = YES;
    }

    return RETURN_SUCCESS;
}

static int VNK_ProcessFD(FILE *File)
{
    // Read+Write permission when open a file
    #define VNK_RDWR "w+"

    int ret = RETURN_SUCCESS;
    char VNK_TestFileDir[PATH_MAX];
    char VNK_TestFilePath[PATH_MAX];
    char VNK_TestFileName[] = "VNK_TestFile.txt";


    // Get current directory where the excutable is placed
    if(getcwd(VNK_TestFileDir, (size_t)PATH_MAX) == NULL)
    {
        ret = errno; // errno from errno.h
        vnk_error_notify(errno, "getcwd(), in function %s", __FUNCTION__);
        goto EndFunction;
    }
    // vnk_debug_notify("inside %s, VNK_TestFileDir=%s",
    //                                         __FUNCTION__, VNK_TestFileDir);

    sprintf(VNK_TestFilePath, "%s/%s", VNK_TestFileDir, VNK_TestFileName);
    // vnk_debug_notify("inside %s, VNK_TestFilePath=%s",
    //                                         __FUNCTION__, VNK_TestFilePath);

    // After open, pass File outside, so do not close it in this function
    File = fopen(VNK_TestFilePath, VNK_RDWR);
    if (File == NULL)
    {
        // errno from errno.h
        ret = errno;
        vnk_error_notify(errno, "fopen() inside %s()", __FUNCTION__);
        goto EndFunction;
    }


EndFunction:

    if(ret != RETURN_SUCCESS)
    {
        // Clean up
        if(File != NULL)
        {
            vnk_debug_notify("inside function %s, line %d",
                        __FUNCTION__, __LINE__);
            fclose(File); // Do not check error
        }

        // There will be something more
        return RETURN_FAILURE;
    }
    return RETURN_SUCCESS;
}

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

int VNK_MiddleFuncGetFP(FILE *File)
{
    VNK_TRACE_NOTIFY("run into %s", __FUNCTION__);

    // Call local function process File
    VNK_ProcessFD(File);

    return RETURN_SUCCESS;
}

int main (int argc, char *argv[])
{
    int ret;
    FILE *L_FD;

    /*
     * Welcome First
     */
    vnk_info_notify("%s", WC);

    /*
     * Init Some Thing
     */
    ret = VNK_Init();
    if(ret == RETURN_FAILURE)
    {
        vnk_error_notify(NO_ERRNO, "issue in %s", __FUNCTION__);
        goto EndPoint;
    }

    /*
     * Run important functions
     */
     VNK_MiddleFuncGetFP(L_FD);

EndPoint:

    vnk_debug_notify("comming to endpoint");

    // Clean Up
    if (L_FD != NULL)
    {
        vnk_debug_notify("inside function %s, line %d",
                    __FUNCTION__, __LINE__);
        fclose(L_FD); // Do not check error
    }

    if (ret == RETURN_FAILURE)
    {
        return RETURN_FAILURE;
    }

    return EXIT_SUCCESS;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/