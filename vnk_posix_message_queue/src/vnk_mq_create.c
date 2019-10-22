/*******************************************************************************
 *
 *      VINA KNOWLEDGE
 *
 *      Site : https://www.vinaknowledge.com
 *      Email: hvloi@vinaknowledge.com
 *
 *      Copyright © 2019 Vina Knowledge
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>

#include "vnk_mq_poxis.h"

/* @NOTICE:
 *  Compile with -lrt option
 */

int opt_parsing_1(int argc, char *argv[], struct mq_attr *mq_attr_p);

int opt_parsing_1(int argc, char *argv[], struct mq_attr *mq_attr_p)
{
    int flags, opt;
    mode_t perms;
    mqd_t mqd;
    struct mq_attr attr, *attrp;

    attrp = NULL;
    attr.mq_maxmsg = 50;
    attr.mq_msgsize = 2048;
    flags = O_RDWR;

    /* Parse command-line options */
    while ((opt = getopt(argc, argv, "cm:s:x")) != -1)
    {
        switch (opt)
        {
            case 'c':
                flags |= O_CREAT;
                break;

            case 'm':
                attr.mq_maxmsg = atoi(optarg);
                attrp = &attr;
                break;

            case 's':
                attr.mq_msgsize = atoi(optarg);
                attrp = &attr;
                break;

            case 'x':
                flags |= O_EXCL;
                break;

            default:
                return RETURN_FAILURE;
        }
    }

    if(optind >= argc)
    {
        return RETURN_FAILURE;
    }

    perms = (S_IRUSR | S_IWUSR);

    mqd = mq_open(argv[optind], O_RDWR | O_CREAT | O_EXCL, S_IRWXU | S_IRWXG, NULL);

    if(mqd == (mqd_t)-1)
    {
        fprintf(stderr, "ERROR: mq_open()\n");
    }

    mq_attr_p = attrp;

    return RETURN_SUCCESS;
}

