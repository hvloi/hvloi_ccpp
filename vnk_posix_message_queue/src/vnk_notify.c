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
 *******************************************************************************
 ******************************************************************************/

/*******************************************************************************
 *********************************INCLUDES**************************************
 ******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "vnk_notify.h"

#define ERR stderr
#define OUT stdout
#define MAX_NOTIFIY_LEN 128

void vnk_error_notify(const char *message, int errnum)
{
    char notify_str[MAX_NOTIFIY_LEN];

    if(errnum)
    {
        snprintf(notify_str, MAX_NOTIFIY_LEN, "%s - %s", message,
                    strerror(errnum));
    }
    else
    {
        strncpy(notify_str, message, MAX_NOTIFIY_LEN);
    }
    fprintf(ERR, "\n");
    fprintf(ERR, "[ERROR]: %s\n\n", notify_str);
    fprintf(ERR, "\n\n");

    return;
}

/*
 * Show INFO
 */
void vnk_info_notify(const char *message)
{
    fprintf(OUT, "[INFO]: %s\n\n", message);

    return;
}
