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
 * Global includes
 **/
#include <stdio.h>
#include <stdlib.h>

/**
 * VNK includes
 **/
#include "VNK_LinkedListExample.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

static void VNK_Welcome()
{
#define OUT stdout

    fprintf(OUT, "\n"                           );
    fprintf(OUT, "WELCOME TO %s\n",          Iam);
    fprintf(OUT, "---------------------------\n");
    fprintf(OUT, "An example from %s\n", MR_BOSS);
    fprintf(OUT, "\n"                           );
    fprintf(OUT, "---------------------------\n");

return;
}

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

/**
 * |------|------|        |------|------|
 * | DATA | NEXT |------->| DATA | NEXT |--------> XXXX
 * |------|------|        |------|------|
 **/

int main(int argc, char *argv[])
{
    int ExitCode;
    int NodeNum;
    int index;
    lili_node_t *head_node;

    VNK_Welcome();

    ExitCode = EXIT_SUCCESS;
    NodeNum = 5; // Temporary, hard code        //
    index = 0;

    // Init the list with first node as head    //
    head_node = (lili_node_t*) malloc(sizeof(lili_node_t));
    if(head_node == NULL)
    {
        vnk_error_notify(NO_ERRNO, "count not init head node");
        ExitCode = EXIT_FAILURE;
        goto EndPoint;
    }
    // IMPORTANT:                               //
    head_node->val  = 0;
    head_node->next = NULL;

    // Add nodes to list                        //
    vnk_info_notify("pushing nodes to list:");
    for(index = 1; index <= NodeNum; index++)
    {
        vnk_debug_notify("pushing node number %d", index);
        if(lili_push(index, &head_node) != RETURN_SUCCESS)
        {
            vnk_error_notify(NO_ERRNO, "count not push node");
            ExitCode = EXIT_FAILURE;
            goto EndPoint;
        }
    }

    // Show value of list nodes                 //
    lili_list(head_node);

    // Remove nodes from list                   //
    vnk_info_notify("poping nodes from list:");
    for(index = 1; index <= NodeNum; index++)
    {
        vnk_debug_notify("poping node number %d", index);
        if(lili_pop(&head_node) != RETURN_SUCCESS)
        {
            vnk_error_notify(NO_ERRNO, "count not pop node");
            ExitCode = EXIT_FAILURE;
            goto EndPoint;
        }
    }

    // Check if the list is empty               //
    if(head_node != NULL && head_node->next == NULL)
    {
        vnk_debug_notify("list has only one node");
        free(head_node);
        head_node = NULL;
        vnk_debug_notify("list is now empty");
    }

/**
 * Question:
 * Is Malloc-ed memory freed automatically after exit process ?
 **/
EndPoint:
    exit(ExitCode);
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
