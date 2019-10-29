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

/* @NOTICE:
 * Compile with -lrt option
 */

static void bye()
{
    // Replace by notify function
    fprintf(stdout, ">> All Done! Bye!\n");
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
    if(l_config.isCreate)
    {
        if(vnk_mq_create(&l_config))
        {
            hasErr = YES;
        }
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
