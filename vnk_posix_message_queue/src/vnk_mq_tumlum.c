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
int opt_parsing(int argc, char *argv[], struct mq_attr *mq_attr_p,
            struct vnkmq_config *l_vnkmq_config)
{
    int flags, opt, modes;
    mode_t perms;
    mqd_t mqd;
    struct mq_attr attr;
    struct vnkmq_config config;
    bool hasErr = NO;
    bool hasAction = false;

    /*
     * NOTE:
     * mq_maxmsg and mq_msgsize may be different in other devices
     */
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;

    flags = O_RDWR;

    /* NEED an attention */
    modes = S_IRUSR | S_IWUSR;

    memset(&config, 0, (size_t)sizeof(struct vnkmq_config));

    /* 
     * Parse command-line options
     * Will try with >>> getopt_long() <<<
     */
    while ((opt = getopt(argc, argv, "m:s:n:a:c:hvtex")) != -1)
    {
        switch (opt)
        {
            case 'm':
                attr.mq_maxmsg = atoi(optarg);
                break;

            case 's':
                attr.mq_msgsize = atoi(optarg);
                break;

            case 'x':
                flags |= O_EXCL;
                break;

            case 'a':
                hasAction = true;

                if (strncmp(optarg, ACTION_CREATE_STRING, MAX_ACTION_SIZE) == 0)
                {
                    config.action = ACTION_CREATE;
                    flags |= O_CREAT;
                }

                else 
                if (strncmp(optarg, ACTION_OPEN_STRING, MAX_ACTION_SIZE) == 0)
                {
                    config.action = ACTION_OPEN;
                }

                else
                if (strncmp(optarg, ACTION_UNLINK_STRING, MAX_ACTION_SIZE) == 0)
                {
                    config.action = ACTION_UNLINK;
                }

                else
                if (strncmp(optarg, ACTION_EDIT_STRING, MAX_ACTION_SIZE) == 0)
                {
                    config.action = ACTION_EDIT;
                }

                else
                if (strncmp(optarg, ACTION_SEND_STRING, MAX_ACTION_SIZE) == 0)
                {
                    config.action = ACTION_SEND;
                }

                else
                if (strncmp(optarg, ACTION_RECIEVE_STRING,
                                                        MAX_ACTION_SIZE) == 0)
                {
                    config.action = ACTION_RECIEVE;
                }

                else
                {
                    config.action = ACTION_UNDEFINE;
                    hasErr = YES;
                    vnk_error_notify(NO_ERRNO, "action \"%s\" is undefined!",
                                optarg);
                    goto out;
                }

                break;

            case 'n':
                strncpy(config.mq_name, optarg, MAX_NAME_SIZE);
                break;

            case 'c':
                strncpy(config.mq_message, optarg, MAX_MESSAGE_SIZE);
                break;

            case 't':
                traceIsEnabled = YES;
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

    if(strncmp(config.mq_name, "", MAX_NAME_SIZE) == 0)
    {
        vnk_error_notify(NO_ERRNO, "queue name is required!");
        hasErr = YES;
        goto out;
    }

    if(!hasAction)
    {
        vnk_error_notify(NO_ERRNO, "action is required!");
        hasErr = YES;
        goto out;
    }

    if(config.action != ACTION_CREATE && (flags & O_EXCL))
    {
        vnk_error_notify(NO_ERRNO, "O_EXCL is only used with action create");
        hasErr = YES;
        goto out;
    }

out:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    /* Copy attributes struct */
    mq_attr_p->mq_maxmsg = attr.mq_maxmsg;
    mq_attr_p->mq_msgsize = attr.mq_msgsize;

    // DBG
    // vnk_debug_notify("in \"%s\" mq_attr_p->mq_msgsize=%d", __FUNCTION__,
    //             mq_attr_p->mq_msgsize);

    // memcpy and "=" operation which is better ?
    // memcpy(l_vnkmq_config, &config, sizeof(config));
    // *l_vnkmq_config = config; <<-- think good!
    // Just copy elements
    strncpy(l_vnkmq_config->mq_name, config.mq_name, MAX_NAME_SIZE);
    strncpy(l_vnkmq_config->mq_message, config.mq_message, MAX_MESSAGE_SIZE);
    l_vnkmq_config->action = config.action;
    l_vnkmq_config->mq_oflag = flags;
    l_vnkmq_config->mq_mode = modes;

    // Debug
    // vnk_debug_notify("in \"%s\", flags = %d", __FUNCTION__, flags);

    return RETURN_SUCCESS;
}

/*
 * This is option string "m:s:n:a:hvtecx"
 */
void usageError(const char *progName)
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s [-xvht] [-m <maxmsg>] [-s <msgsize>]\n"
                    "       [-p <octal-perms>] {-n <queue name>}\n"
                    "       {-a <action>}\n\n", progName);
    fprintf(stderr, "       -d  unlink queue <queue name>\n");
    fprintf(stderr, "       -m  maxmsg set maximum number of messages\n");
    fprintf(stderr, "       -s  msgsize set maximum message size\n");
    fprintf(stderr, "       -x  create exclusively (O_EXCL)\n");
    fprintf(stderr, "       -n  name of queue\n");
    fprintf(stderr, "       -a  action of the call <create|open|unlink>\n");
    fprintf(stderr, "       -t  trace, show step of code\n");
    fprintf(stderr, "       -c  content of message if action is send");
    fprintf(stderr, "       -v  show version\n");
    fprintf(stderr, "       -h  show this help\n");
    fprintf(stderr, "       -e  edit, set/clear O_NONBLOCK attribute of MQ\n");
    fprintf(stderr, "\n\n");
}

void showVersion()
{
    fprintf(stdout, "\n");
    fprintf(stdout, "* * * * * * * * * * * * * * * * * * *\n");
    fprintf(stdout, "* * * V I N A K N O W L E D G E * * *\n");
    fprintf(stdout, "* * * * * * * * * * * * * * * * * * *\n");
    fprintf(stdout, "[     vnkmq  -  %s     ]\n", VERSION_YEAR);
    fprintf(stdout, "[     Version:  %d.%d  ]\n", VERSION_MAJOR, VERSION_MINOR);
    fprintf(stdout, "* * * * * * * * * * * * * * * * * * *\n");
    fprintf(stdout, "* * * * * * * * * * * * * * * * * * *\n");
    fprintf(stdout, "\n\n");
}
