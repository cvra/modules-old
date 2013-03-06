#ifndef _RDLINE_CONFIG_H_
#define _RDLINE_CONFIG_H_


/** @def CONFIG_MODULE_RDLINE_HISTORY
 * @brief Enables history.
 * 
 * If this is defined, the rdline module supports history via arrow up/down.
 */
#define CONFIG_MODULE_RDLINE_HISTORY


/** @def CONFIG_MODULE_RDLINE_KILL_BUF
 * @brief Enables cut paste.
 *
 * If this is defined, the rdline module supports bash style cut/paste using Ctrl-K and Ctrl-Y.
 */
#define CONFIG_MODULE_RDLINE_KILL_BUF

#endif
