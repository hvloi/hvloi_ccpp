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

#ifndef VNK_MQ_POXIS_H
#define VNK_MQ_POXIS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>

#include "tlpi_hdr.h"


/*******************************************************************************
 **********************************GLOBAL***************************************
 ******************************************************************************/

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RETURN_FAILURE 1
#define RETURN_SUCCESS 0

#define MAX_NAME_SIZE   32
#define MAX_ACTION_SIZE 8

#define ACTION_CREATE_STRING "create"
#define ACTION_OPEN_STRING   "open"
#define ACTION_UNLINK_STRING "unlink"

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_YEAR  "Oct 2019"

// Define has error
#define YES true
#define NO  false

/*
 * Use of extern:
 * In real world, multi-file programs, extern declarations are normally
 * contained in a header file that is simply included with each source code
 * file. This is both easier and less error prone than manually duplicating
 * extern declarations in each file.
 */
extern bool traceIsEnabled;

typedef enum {
    ACTION_UNDEFINE = 0,
    ACTION_OPEN        ,
    ACTION_CREATE      ,
    ACTION_UNLINK
} mq_action;

struct vnkmq_config
{
    // MQ action
    mq_action   action;
    // MQ name
    char        mq_name[MAX_NAME_SIZE];
    // MQ oflag
    int         mq_oflag;
    // MQ modes
    int         mq_mode;
    // MQ descriptor
    mqd_t       mq_d;
};

/*
 * Some Description....
 */
int opt_parsing(int argc, char *argv[], struct mq_attr *mq_attr_p, struct vnkmq_config *l_vnkmq_config);

/*
 * Some Description....
 */
void usageError(const char *progName);

/*
 * Some description....
 */
void showVersion();

/*
 * Some Description....
 */
int vnk_mq_create(struct vnkmq_config *l_vnkmq_config,
            struct mq_attr *l_mq_attr);

/*
 * Function : vnk_mq_create
 * Input    : message queue name
 * Output   : RETURN_SUCCESS / RETURN_FAILURE
 * NOTE     : xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 */
int vnk_mq_unlink(const char *mq_name);

/*
 * Function : vnk_mq_retrieve
 * Input    :
 * Output   :
 * NOTE     : xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 */
int vnk_mq_retrieve(const char *mq_name);

/*******************************************************************************
 **********************************PRIVATE**************************************
 ******************************************************************************/

#endif /* VNK_MQ_POXIS_H */
