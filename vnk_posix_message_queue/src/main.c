/*******************************************************************************
 *******************************************************************************
 **
 **      VINA KNOWLEDGE
 **
 **      Site : https://www.vinaknowledge.com
 **      Email: hvloi@vinaknowledge.com
 **
 **      Copyright © 2019 Vina Knowledge
 **
 ******************************************************************************/

/*******************************************************************************
 *********************************INCLUDES**************************************
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <stdbool.h>

#include "vnk_mq_poxis.h"


/*******************************************************************************
 **********************************GLOBAL***************************************
 ******************************************************************************/

/*******************************************************************************
 **********************************PRIVATE**************************************
 ******************************************************************************/

/* 
 * @NOTICE:
 * Compile with -lrt option
 */

/*
 * Function: 
 */
static void bye();
static void looploop();

static void bye()
{
    // Replace by notify function
    fprintf(stdout, ">> All Done! Bye!\n");
}

/*
 * Under contruction,....
 */
static void looploop()
{
    while(1)
    {
        sleep(10);
    }

    return;
}

int main(int argc, char *argv[])
{
    bool hasErr = NO;
    struct mq_attr l_attr;
    struct vnkmq_config l_config;

    memset(&l_config, 0, (size_t)sizeof(struct vnkmq_config));

    if(argc <= 1)
    {
        usageError(argv[0]);
        hasErr = YES;
        goto bye_bye;
    }

    // Get options
    if(opt_parsing(argc, argv, &l_attr, &l_config))
    {
        hasErr = YES;
        goto bye_bye;
    }

    // Process option
    if(l_config.action == ACTION_CREATE)
    {
        if(vnk_mq_create(&l_config) == 1) // return = 1 is in error
        {
            hasErr = YES;
            goto bye_bye;
        }
    }
    else if (l_config.action == ACTION_OPEN)
    {
        // Something here,...
    }
    else if (l_config.action == ACTION_UNLINK)
    {
        // Do something,...
        if(vnk_mq_unlink(l_config.q_name) == 1)
        {
            hasErr = YES;
            goto bye_bye;
        }
    }
    else
    {
        hasErr = YES;
    }

bye_bye:
    if(hasErr)
    {
        exit(EXIT_FAILURE);
    }

    // Bye bye if no error, otherwise show error and stop
    bye();

    exit(EXIT_SUCCESS);
}
