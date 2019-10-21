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

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

/* @NOTICE:
 *  Compile with -lrt option
 */

static void usageError(const char *progName)
{
    fprintf(stderr, "Usage: %s [-cx] [-m maxmsg] [-s msgsize] mq-name "
                    "[octal-perms]\n", progName);
    fprintf(stderr, "       -c create queue (O_CREAT)\n");
    fprintf(stderr, "       -m maxmsg set maximum # of messages\n");
    fprintf(stderr, "       -s msgsize set maximum message size\n");
    fprintf(stderr, "       -x create exclusively (O_EXCL)\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
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
                usageError(argv[0]);
        }
    }

    if(optind >= argc)
    {
        usageError(argv[0]);
    }

    perms = (S_IRUSR | S_IWUSR);

    mqd = mq_open(argv[optind], O_RDWR | O_CREAT | O_EXCL, S_IRWXU | S_IRWXG, NULL);

    if(mqd == (mqd_t)-1)
    {
        fprintf(stderr, "ERROR: mq_open()\n");
    }

    exit(EXIT_SUCCESS);
}

