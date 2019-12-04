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

    /* Enable / Disable Notify Trace */
    if(strncmp(ENABLE_NOTIFY_TRACE, "YES", strlen("YES")) == 0)
    {
        // vnk_debug_notify("inside %s line %d", __FUNCTION__, __LINE__);
        VNK_GlobalTraceIsEnabled = YES;
    }

    return RETURN_SUCCESS;
}

static int VNK_ProcessFD(FILE *File1, FILE **File2)
{
    /**
     * Read+Write permission when open a file
     **/
    #define VNK_RDWR "w+"

    int ret = RETURN_SUCCESS;
    char VNK_TestFileDir[PATH_MAX];
    char VNK_TestFile1Path[PATH_MAX];
    char VNK_TestFile2Path[PATH_MAX];
    char VNK_TestFile1Name[] = "VNK_TestFile_1.txt";
    char VNK_TestFile2Name[] = "VNK_TestFile_2.txt";


    // Get current directory where the excutable is placed
    if(getcwd(VNK_TestFileDir, (size_t)PATH_MAX) == NULL)
    {
        ret = errno; // errno from errno.h
        vnk_error_notify(errno, "getcwd(), in function %s()", __FUNCTION__);
        goto EndFunction;
    }
    // vnk_debug_notify("inside %s, VNK_TestFileDir=%s",
    //                                         __FUNCTION__, VNK_TestFileDir);

    /* Set Path to File1 */
    sprintf(VNK_TestFile1Path, "%s/%s", VNK_TestFileDir, VNK_TestFile1Name);
    /* Set Path to File2 */
    sprintf(VNK_TestFile2Path, "%s/%s", VNK_TestFileDir, VNK_TestFile2Name);
    // vnk_debug_notify("inside %s, VNK_TestFile1Path=%s",
    //                                         __FUNCTION__, VNK_TestFile1Path);

    /* After open, pass File outside, so do not close it in this function */
    VNK_TRACE_NOTIFY("Step 3: open File1");
    File1 = fopen(VNK_TestFile1Path, VNK_RDWR);
    if (File1 == NULL)
    {
        /* errno from errno.h */
        ret = errno;
        vnk_error_notify(errno, "fopen() inside %s()", __FUNCTION__);
        goto EndFunction;
    }
    else
    {
        VNK_TRACE_NOTIFY("Step 4: File1 is not null in %s()", __FUNCTION__);
        VNK_TRACE_NOTIFY("File1=%p", File1);
    }
    VNK_TRACE_NOTIFY("Step 5: open File2");
    *File2 = fopen(VNK_TestFile2Path, VNK_RDWR);
    if (*File2 == NULL)
    {
        /* errno from errno.h */
        ret = errno;
        vnk_error_notify(errno, "fopen() inside %s()", __FUNCTION__);
        goto EndFunction;
    }
    else
    {
        VNK_TRACE_NOTIFY("Step 6: File2 is not null in %s()", __FUNCTION__);
        VNK_TRACE_NOTIFY("File2=%p", *File2);
    }


EndFunction:

    if(ret != RETURN_SUCCESS)
    {
        /* Clean up */
        if(File1 != NULL)
        {
            vnk_debug_notify("inside function %s(), line %d",
                        __FUNCTION__, __LINE__);
            fclose(File1); // Do not check error
        }
        else if(*File2 != NULL)
        {
            vnk_debug_notify("inside function %s(), line %d",
                        __FUNCTION__, __LINE__);
            fclose(*File2); // Do not check error
        }

        /* There will be something more */
        return RETURN_FAILURE;
    }
    return RETURN_SUCCESS;
}

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

int VNK_MiddleFuncGetFP(FILE *File1, FILE **File2)
{
    VNK_TRACE_NOTIFY("Run into %s()", __FUNCTION__);

    /* Call local function process File */
    VNK_TRACE_NOTIFY("Step 2: Passing two FDs to VNK_ProcessFD()");
    VNK_ProcessFD(File1, File2);

    if (File1 != NULL)
    {
        VNK_TRACE_NOTIFY("Step 7: File1 is NOT NULL in %s()", __FUNCTION__);
        VNK_TRACE_NOTIFY("File1=%p", File1);
    }

    if (*File2 != NULL)
    {
        VNK_TRACE_NOTIFY("Step 8: File2 is NOT NULL in %s()", __FUNCTION__);
        VNK_TRACE_NOTIFY("File2=%p", *File2);
    }

    return RETURN_SUCCESS;
}

int main (int argc, char *argv[])
{
    int ret;
    FILE *L_FD1;
    FILE *L_FD2;

    /**
     * Welcome First
     **/
    vnk_info_notify("%s", WC);

    /**
     * Init Some Thing
     **/
    ret = VNK_Init();
    if(ret == RETURN_FAILURE)
    {
        vnk_error_notify(NO_ERRNO, "issue in %s()", __FUNCTION__);
        goto EndPoint;
    }

    /**
     * Run important functions
     **/

     VNK_TRACE_NOTIFY("Step 1: passing two FDs to VNK_MiddleFuncGetFP()");
     VNK_MiddleFuncGetFP(L_FD1, &L_FD2);

    if (L_FD1 != NULL)
    {
        VNK_TRACE_NOTIFY("Step 9: File1 is NOT NULL in %s()", __FUNCTION__);
        VNK_TRACE_NOTIFY("File1=%p", L_FD1);
    }

    if (L_FD2 != NULL)
    {
        VNK_TRACE_NOTIFY("Step 10: File2 is NOT NULL in %s()", __FUNCTION__);
        VNK_TRACE_NOTIFY("File2=%p", L_FD2);
    }

EndPoint:

    vnk_debug_notify("Comming to endpoint...");

    /* All works are done, clean up and exit */

    if (L_FD1 != NULL)
    {
        vnk_debug_notify("Inside function %s(), line %d",
                    __FUNCTION__, __LINE__);

        /**
         * Cannot close L_FD1 because it is holding an unknow FILE discriptor.
         * This is what these code demonstrate
         **/
        /* Un-comment following fclose() function to see what happen */
        // fclose(L_FD1); // Do not check error
    }

    if (L_FD2 != NULL)
    {
        vnk_debug_notify("Inside function %s(), line %d",
                    __FUNCTION__, __LINE__);
        fclose(L_FD2); // Do not check error
    }

    if (ret == RETURN_FAILURE)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/