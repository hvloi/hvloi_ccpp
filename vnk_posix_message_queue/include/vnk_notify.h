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

#ifndef VNK_NOTIFY
#define VNK_NOTIFY

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


#endif /*VNK_NOTIFY*/
