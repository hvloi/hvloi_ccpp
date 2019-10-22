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

#include "vnk_mq_poxis.h"


/*******************************************************************************
 **********************************GLOBAL***************************************
 ******************************************************************************/

/*******************************************************************************
 **********************************PRIVATE**************************************
 ******************************************************************************/

static void usageError(const char *progName)
{
    fprintf(stderr, "Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name "
                    "[octal-perms]\n", progName);
    fprintf(stderr, "       -c create queue (O_CREAT)\n");
    fprintf(stderr, "       -m maxmsg set maximum # of messages\n");
    fprintf(stderr, "       -s msgsize set maximum message size\n");
    fprintf(stderr, "       -x create exclusively (O_EXCL)\n");
}

int main(int argc, char *argv[])
{
    int err;
    struct mq_attr l_attr;

    printf(">> DBG: enter main()\n");

    err = opt_parsing(argc, argv, &l_attr);
    if(err)
    {
        goto bye_bye;
    }

bye_bye:
    if(err)
    {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
