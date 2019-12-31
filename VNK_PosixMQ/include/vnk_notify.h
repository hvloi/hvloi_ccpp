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

#ifndef VNK_NOTIFY
#define VNK_NOTIFY

/*
 * Used for vnk_error_notify() to indecate that
 * there is no errno
 */
#define NO_ERRNO 0

/*
 * MACRO  : VNK_TRACE_NOTIFY
 * Input  : message
 * Output :
 * Comment: this macro includes two steps of show strace notify:
 *          1. Check if tracIsEnabled
 *          2. If (1) is true, show strace message
 * N O T E: No space between e.i VNK_TRACE_NOTIFY<nospace>()
 */
#define VNK_TRACE_NOTIFY( fmt, args... ) \
    do \
    { \
        if (traceIsEnabled) \
        { \
            vnk_trace_notify (fmt , ##args); \
        } \
    } \
    while (0)

/*
 * Function : vnk_error_notify
 * Input    :
 * Output   :
 * NOTE     : xXxXxX
 */
int vnk_error_notify(int errnum, const char *message, ...);

/*
 * Function : vnk_info_notify
 * Input    :
 * Output   :
 * NOTE     : xXxXxX
 */
int vnk_info_notify(const char *message, ...);

/*
 * Function : vnk_trace_notify
 * Input    :
 * Output   :
 * NOTE     : xXxXxX
 */
int vnk_trace_notify(const char *message, ...);

/*
 * Function : vnk_debug_notify
 * Input    :
 * Output   :
 * NOTE     : xXxXxX
 */
int vnk_debug_notify(const char *message, ...);

#endif /*VNK_NOTIFY*/
