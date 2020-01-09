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

#ifndef VNK_LINKED_LIST_EXAMPLE_H
#define VNK_LINKED_LIST_EXAMPLE_H

/**
 * Author:
 * Loi Huynh
 *
 * References:
 * 1. https://www.learn-c.org/en/Linked_lists
 **/

/******************************************************************************\
*******************************I*N*C*L*U*D*E*S**********************************
\******************************************************************************/

/**
 * VNK Includes
 **/
#include "vnk_lib_notify.h"

/******************************************************************************\
****************************D*E*F*I*N*I*T*I*O*N*S*******************************
\******************************************************************************/

#define MR_BOSS  "Loi Huynh"
#define Iam      "VNKLILI"

/**
 * These following definitions should be moved to a library
 **/

#define EXIT_FAILURE   1
#define EXIT_SUCCESS   0

#define RETURN_FAILURE 1
#define RETURN_SUCCESS 0

#define YES  true
#define NO   false

/******************************************************************************\
********************************G*L*O*B*A*L*S***********************************
\******************************************************************************/

typedef struct VNK_LinkedListNode
{
    int val;
    struct VNK_LinkedListNode *next;
} lili_node_t;

/******************************************************************************\
********************************P*R*I*V*A*T*E***********************************
\******************************************************************************/

/******************************************************************************\
*******************************M*A*I*N*C*O*D*E**********************************
\******************************************************************************/

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
int lili_push(int c_val, lili_node_t **head);

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
int lili_pop(lili_node_t **head);

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
void lili_list(lili_node_t *head);

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
int lili_PushEnd(lili_node_t *head, int c_val);

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
int lili_NodeNum(lili_node_t *head);

/******************************************************************************\
************************************E*N*D***************************************
\******************************************************************************/

#endif // VNK_LINKED_LIST_EXAMPLE_H //
