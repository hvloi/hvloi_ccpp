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
#include <stdarg.h>

#include "vnk_mq_poxis.h"
#include "vnk_notify.h"

#define ERR stderr
#define OUT stdout
#define MAX_NOTIFIY_LEN 2048


/*
 * Show ERRO
 */
int vnk_error_notify(int errnum, const char *message, ...)
{
    bool hasErr = NO;
    char vsbuff[1024];
    char notify_str[MAX_NOTIFIY_LEN];
    int return_code;
    va_list args;

    /* Build message */
    va_start(args, message);
    return_code = vsprintf(vsbuff, message, args);
    va_end(args);

    if(return_code < 0)
    {
        hasErr = YES;
        goto quick;
    }

    if(errnum)
    {
        snprintf(notify_str, MAX_NOTIFIY_LEN, "%s - %s", vsbuff,
                    strerror(errnum));
    }
    else
    {
        strncpy(notify_str, vsbuff, MAX_NOTIFIY_LEN);
    }
    fprintf(ERR, "\n");
    fprintf(ERR, "[ERRO]: %s\n\n", notify_str);
    fprintf(ERR, "\n\n");

quick:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

/*
 * Show INFO
 */
int vnk_info_notify(const char *message, ...)
{
    bool hasErr = NO;
    char vsbuff[1024];
    int return_code;
    va_list args;

    /* Build message */
    va_start(args, message);
    return_code = vsprintf(vsbuff, message, args);
    va_end(args);

    if(return_code < 0)
    {
        hasErr = YES;
        goto quick;
    }
    fprintf(OUT, "\n");
    fprintf(OUT, "[INFO]: %s", vsbuff);
    fprintf(OUT, "\n\n");

quick:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

/*
 * Show TRAC
 */
int vnk_trace_notify(const char *message, ...)
{
    bool hasErr = NO;
    char vsbuff[1024];
    int return_code;
    va_list args;

    /* Build message */
    va_start(args, message);
    return_code = vsprintf(vsbuff, message, args);
    va_end(args);

    if(return_code < 0)
    {
        hasErr = YES;
        goto quick;
    }
    fprintf(OUT, "\n");
    fprintf(OUT, "[TRAC]: %s", vsbuff);
    fprintf(OUT, "\n\n");

quick:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

/*
 * Show TRAC
 */
int vnk_debug_notify(const char *message, ...)
{
    bool hasErr = NO;
    char vsbuff[1024];
    int return_code;
    va_list args;

    /* Build message */
    va_start(args, message);
    return_code = vsprintf(vsbuff, message, args);
    va_end(args);

    if(return_code < 0)
    {
        hasErr = YES;
        goto quick;
    }
    fprintf(OUT, "\n");
    fprintf(OUT, "[DBUG]: %s", vsbuff);
    fprintf(OUT, "\n\n");

quick:
    if(hasErr)
    {
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}
