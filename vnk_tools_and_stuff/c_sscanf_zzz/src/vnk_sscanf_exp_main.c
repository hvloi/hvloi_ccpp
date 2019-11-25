/******************************************************************************\
********************************************************************************
**                                                                            **
**                          VNK - VINA KNOWLEDGE                              **
**                                                                            **
**                   Site : https://www.vinaknowledge.com                     **
**                   Email: hvloi@vinaknowledge.com                           **
**                                                                            **
**                     Copyright © 2019 Vina Knowledge                        **
**                                                                            **
********************************************************************************
\******************************************************************************/



/*******************************************************************************
 *********************************INCLUDES**************************************
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 **********************************GLOBAL***************************************
 ******************************************************************************/

#define EXIT_OK 0
#define EXIT_KO 1

/*******************************************************************************
 **********************************PRIVATE**************************************
 ******************************************************************************/

/******************************************************************************\
********************************M*A*I*N*C*O*D*E*********************************
\******************************************************************************/

/*

[ V E R Y  D I R T Y  C O D E ]

 */

/*
 * W H A T  W E  C A N  L E A R N  ?!
 * 1. scanset: https://www.geeksforgeeks.org/scansets-in-c/
 * 2. sscanf : https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/
 *             com.ibm.zos.v2r1.ccrug00/sscanf.htm#sscanf__fscanty
 */


void case_1 ()
{
    char  input[] = "COLOR: /yellow 23.5%% |/lor/red 8.4%% |/col_z/blue 24.2%%";

    // Original format "%*[^r]%*[^ ] %[^%]"
    char format[] = "%*[^u]%*[^ ]%[^%]";

    char output[32];
    int  numread = 0;

    output[0] = '\0';

    numread = sscanf(input, format, output);

    printf("[INP] input = %s\n", input);

    printf("[RES] numread = %d\n", numread);
    printf("[RES] output = >|%s|<\n", output);

    return;
}

void case_2 ()
{
    char  input[] = "abc def ghk lmn";

    /*
     * E X P L A I N:
     * 1.
     */
    char format[] = "%*[^k]%*[^ ]%[^\n]";

    char output[32];
    int  numread = 0;

    output[0] = '\0';

    numread = sscanf(input, format, output);

    printf("[INP] input = %s\n", input);

    printf("[RES] numread = %d\n", numread);
    printf("[RES] output = >|%s|<\n", output);


    return;
}

int main ()
{
    // CHECK CASE BY CASE

    // case_1();
    case_2();


    exit(EXIT_OK);
}
