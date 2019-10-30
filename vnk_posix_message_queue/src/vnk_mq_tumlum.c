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
#include "vnk_notify.h"


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
    bool hasErr = NO;
    bool hasAction = false;

    attrp = NULL;
    attr.mq_maxmsg = 50;
    attr.mq_msgsize = 2048;
    flags = O_RDWR;
    memset(&config, 0, (size_t)sizeof(struct vnkmq_config));

    /* 
     * Parse command-line options
     * Will try with >>> getopt_long() <<<
     */
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
                hasAction = true;

                if (strncmp(optarg, ACTION_CREATE_STRING, MAX_ACTION_SIZE) == 0)
                    config.action = ACTION_CREATE;

                else if (strncmp(optarg, ACTION_OPEN_STRING, MAX_ACTION_SIZE) == 0)
                    config.action = ACTION_OPEN;

                else if (strncmp(optarg, ACTION_UNLINK_STRING, MAX_ACTION_SIZE) == 0)
                    config.action = ACTION_UNLINK;

                else
                {
                    config.action = ACTION_UNDEFINE;
                    hasErr = YES;
                    goto out;
                }
                break;

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

    if(strncmp(config.q_name, "", MAX_NAME_SIZE) == 0)
    {
        vnk_error_notify("queue name is required", 0);
        hasErr = YES;
        goto out;
    }

    if(!hasAction)
    {
        vnk_error_notify("action is required", 0);
        hasErr = YES;
        goto out;
    }

out:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    mq_attr_p = attrp;

    // memcpy and "=" operation which is better ?
    // memcpy(l_vnkmq_config, &config, sizeof(config));
    // *l_vnkmq_config = config;
    // Just copy elements
    strncpy(l_vnkmq_config->q_name, config.q_name, MAX_NAME_SIZE);
    l_vnkmq_config->action = config.action;

    return RETURN_SUCCESS;
}

/*
 * This is option string "cm:s:xn:a:"
 */
void usageError(const char *progName)
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name "
                    "[octal-perms]\n", progName);
    fprintf(stderr, "       -c create queue (O_CREAT)\n");
    fprintf(stderr, "       -d <queue-name> unlink queue");
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
