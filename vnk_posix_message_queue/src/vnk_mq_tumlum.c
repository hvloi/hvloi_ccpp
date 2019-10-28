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
 * Function: opt_parsing
 * Author  : Loi Huynh
 */
int opt_parsing(int argc, char *argv[], struct mq_attr *mq_attr_p, struct vnkmq_config *l_vnkmq_config)
{
    int flags, opt;
    mode_t perms;
    mqd_t mqd;
    struct mq_attr attr, *attrp;
    struct vnkmq_config config;

    attrp = NULL;
    attr.mq_maxmsg = 50;
    attr.mq_msgsize = 2048;
    flags = O_RDWR;
    memset(&config, 0, (size_t)sizeof(struct vnkmq_config));

    /* Parse command-line options */
    while ((opt = getopt(argc, argv, "cm:s:xn:a:hv")) != -1)
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

            case 'a':
                if (strncmp(optarg, ACTION_CREATE, MAX_ACTION_SIZE) == 0)
                    config.isCreate = true;
                else if (strncmp(optarg, ACTION_OPEN, MAX_ACTION_SIZE) == 0)
                    config.isCreate = false;
                else
                    return RETURN_FAILURE;

            case 'n':
                strncpy(config.q_name, optarg, MAX_NAME_SIZE);
                break;

            case 'h':
                usageError(argv[0]);
                return RETURN_SUCCESS;

            case 'v':
                showVersion();
                return RETURN_SUCCESS;

            default:
                return RETURN_FAILURE;
        }
    }

    mq_attr_p = attrp;

    // memcpy and "=" operation which is better ?
    // memcpy(l_vnkmq_config, &config, sizeof(config));
    *l_vnkmq_config = config;

    return RETURN_SUCCESS;
}

/*
 * This is option string "cm:s:xn:a:"
 */
void usageError(const char *progName)
{
    fprintf(stderr, "\n\n");
    fprintf(stderr, "Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name "
                    "[octal-perms]\n", progName);
    fprintf(stderr, "       -c create queue (O_CREAT)\n");
    fprintf(stderr, "       -m maxmsg set maximum # of messages\n");
    fprintf(stderr, "       -s msgsize set maximum message size\n");
    fprintf(stderr, "       -x create exclusively (O_EXCL)\n");
    fprintf(stderr, "       -n name of queue\n");
    fprintf(stderr, "       -a action of the call <create|open>\n");
    fprintf(stderr, "       -h show this help\n");
    fprintf(stderr, "\n\n");
}

void showVersion()
{
    fprintf(stdout, "\n");
    fprintf(stdout, "***VINA KNOWLEDGE***\n");
    fprintf(stdout, "   vnkmq - %s\n", VERSION_YEAR);
    fprintf(stdout, "   Version: %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
    fprintf(stdout, "\n\n");
}
