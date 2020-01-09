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

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

/**
 * WHAT IS A LINKED LIST ???
 *________________________________________________
 *
 * |------|------|        |------|------|
 * | DATA | NEXT |------->| DATA | NEXT |--------> XXXX
 * |------|------|        |------|------|
 **/

/**
 * FUNCTION    :
 * lili_push
 *
 * SCOPE       :
 * Global
 *
 * DESCRIPTION :
 * Add new item to be first item of list
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * Push operation, add new item to the head:
 *   1. Create new node and set its val
 *   2. Link the new item to point its next to current head
 *   3. Set new item as head
 **/
int lili_push(int c_val, lili_node_t **head)
{
    int RetCode;
    lili_node_t *new_node;

    new_node = (lili_node_t*) malloc(sizeof(lili_node_t));
    if(new_node == NULL)
    {
        vnk_error_notify(NO_ERRNO, "new lili_node_t allocation, inside %s",
                    __FUNCTION__);
        RetCode = RETURN_FAILURE;
        goto ReturnPoint;
    }

    // Set value for new node                   //
    new_node->next = *head;
    new_node->val  = c_val;

    // Change head                              //
    *head = new_node;

    RetCode = RETURN_SUCCESS;

ReturnPoint:
    return RetCode;
}

/**
 * FUNCTION    :
 * lili_pop
 *
 * SCOPE       :
 * Global
 *
 * DESCRIPTION :
 * Remove first item of the list
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * Pop operation, remove an item from the head:
 * 1. Take the second item (next of the head)
 * 2. Free head item
 * 3. Set the head item that was taken
 **/
int lili_pop(lili_node_t **head)
{
    int RetCode;
    lili_node_t *tmp_node;

    if(*head == NULL)
    {
        vnk_error_notify(NO_ERRNO, "list head is NULL kidding me?, inside %s");
        RetCode = RETURN_FAILURE;
        goto ReturnPoint;
    }

    /**
     * NICE CATCH :
     * It should be "tmp_node = (*head)->next"
     * Do not be "tmp_node = *head->next;"
     **/
    tmp_node = (*head)->next;
    if(tmp_node == NULL)
    {
        vnk_error_notify(NO_ERRNO, "hmmm, list have only one item , inside %s",
                    __FUNCTION__);
        RetCode = RETURN_FAILURE;
        goto ReturnPoint;
    }

    // Free current head           //
    free(*head);

    // Assign head to other item   //
    *head = tmp_node;

    RetCode = RETURN_SUCCESS;

ReturnPoint:
    return RetCode;
}

/**
 * FUNCTION    :
 * lili_list
 *
 * SCOPE       :
 * Global
 *
 * DESCRIPTION :
 * List all items of a list
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 *
 **/
void lili_list(lili_node_t *head)
{
    lili_node_t *current = NULL;

    if(head == NULL)
    {
        vnk_error_notify(NO_ERRNO, "no no no, head is null, inside %s",
                    __FUNCTION__);
        goto ReturnPoint;
    }

    current = head;

    vnk_info_notify("list items are: ");

    while(current != NULL)
    {
        printf(" %d,", current->val);
        current = current->next;
    }
    // Make a space line                        //
    printf("\n\n");

ReturnPoint:
    return;
}

/**
 * FUNCTION    :
 * lili_PushEnd
 *
 * SCOPE       :
 * Global
 *
 * DESCRIPTION :
 * Add new node at the end of list.
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 * To add new node at the end of list:
 * 1. Create new temp node
 * 2. Go to the end of list
 * 3. Next pointer of the last node points to new temp node
 * 4. Next pointer of new node points to NULL
 **/
int lili_PushEnd(lili_node_t *head, int c_val)
{
    int RetCode;
    lili_node_t *new_node;
    lili_node_t *current;

    RetCode = RETURN_SUCCESS;

    if(head == NULL)
    {
        vnk_error_notify(NO_ERRNO, "ahhh you give me a null head, inside %s",
                    __FUNCTION__);
        RetCode = RETURN_FAILURE;
        goto EndPoint;
    }

    /**
     * Question:
     * Should initialize pointer to NULL ?
     **/
    new_node = NULL;
    current = head;

    /* Allocating space for new node */
    new_node = (lili_node_t*) malloc(sizeof(lili_node_t));
    if(new_node == NULL)
    {
        vnk_error_notify(NO_ERRNO, "cound not allocate new node, inside %s",
                    __FUNCTION__);
        RetCode = RETURN_FAILURE;
        goto EndPoint;
    }

    /* Set value of new node */
    new_node->val = c_val;

    /* Set new node as a "tail" (new_node->next = NULL) */
    new_node->next = NULL;

    /* Now find the current "tail" of the list and make a new tail */
    while(current->next != NULL)
    {
        current = current->next;
    }

    /* New "tail" */
    current->next = new_node;

EndPoint:
    return RetCode;
}

/**
 * FUNCTION    :
 * lili_NodeNum
 *
 * SCOPE       :
 * Global
 *
 * DESCRIPTION :
 * Return number of nodes of a list.
 *
 * INPUT       :
 *
 * OUTPUT      :
 *
 * NOTE        :
 *
 **/
int lili_NodeNum(lili_node_t *head)
{
    int NodeNum;
    lili_node_t *current;

    NodeNum = 0;
    current = head;

    if(current == NULL)
    {
        goto EndPoint;
    }

    while(current->next != NULL)
    {
        NodeNum = NodeNum + 1;
        current = current->next;
    }

    /* Including head node */
    NodeNum = NodeNum + 1;

EndPoint:
    return NodeNum;
}

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/
