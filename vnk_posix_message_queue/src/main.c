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



static void bye()
{
    fprintf(stdout, ">> All Done! Bye!\n");
}

int main(int argc, char *argv[])
{
    int err = 0;
    struct mq_attr l_attr;
    struct vnkmq_config l_config;

    memset(&l_config, 0, (size_t)sizeof(struct vnkmq_config));

    if(argc <= 1)
    {
        err = EXIT_FAILURE;
        goto bye_bye;
    }

    err = opt_parsing(argc, argv, &l_attr, &l_config);
    if(err)
    {
        goto bye_bye;
    }

bye_bye:
    if(err)
    {
        usageError(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Bye bye if no error, otherwise show error and stop
    bye();

    exit(EXIT_SUCCESS);
}
