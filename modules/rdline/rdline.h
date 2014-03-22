/*
 *  Copyright Droids Corporation (2007)
 *  Olivier MATZ <zer0@droids-corp.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Revision : $Id: rdline.h,v 1.1.2.6 2009-02-27 21:41:31 zer0 Exp $
 *
 *
 */

#ifndef _RDLINE_H_
#define _RDLINE_H_

/** @file rdline.h
 *
 * This library is a small equivalent to the GNU readline library, but
 * it is designed for small systems, like Atmel AVR microcontrollers
 * (8 bits). Indeed, we don't use any malloc that is sometimes not
 * implemented on such systems.
 */

#include <platform.h>
#include <cirbuf.h>
#include <vt100.h>
#include <rdline_config.h>

/* configuration */
/** Defines the size of the buffer (maximal size of the line input by the user. */
#define RDLINE_BUF_SIZE 64

/** Defines the maximal size of the prompt. */
#define RDLINE_PROMPT_SIZE  16

/** Defines the size of the history buffer. */
#define RDLINE_HISTORY_BUF_SIZE 128

/** Status of the rdline module. */
enum rdline_status {
    RDLINE_INIT,  /**< Module not ready to accept chars. */
    RDLINE_RUNNING, /** < Module ready to accept chars. */
};


/** Prototype of the compatibles write functions. */
typedef void (rdline_write_char_t)(char);

/** Prototype of the compatibles validate buffer functions. */
typedef void (rdline_validate_t)(const char *buf, int size);

/** Prototype of the compatibles complete buffer functions. */
typedef int (rdline_complete_t)(const char *buf, char *dstbuf,
                int dstsize, int *state);

/** @struct rdline
 * @brief An instance of the rdline module.
 *
 * This modules holds everything that a single instance of the rdline module needs
 * such as buffers, history, clipboards, callbacks and so on.
 */
struct rdline {
    enum rdline_status status; /**< Flag to tell if the instance is ready to receive chars. */
    /* rdline bufs */
    struct cirbuf left; /**< Content of the line to the left of the cursor. */
    struct cirbuf right; /**< Content of the line to the right of the cursor. */
    /** Memory buffer for left cirbuf. reserve 2 chars for the \n\0 */
    char left_buf[RDLINE_BUF_SIZE+2];
    char right_buf[RDLINE_BUF_SIZE]; /**< Memory buffer for the right cirbuf. */

    char prompt[RDLINE_PROMPT_SIZE]; /**< Prompt of the command line. */
    uint8_t prompt_size; /**< Length of prompt. */

#ifdef CONFIG_MODULE_RDLINE_KILL_BUF
    char kill_buf[RDLINE_BUF_SIZE]; /**< Kill buffer (clipboard) */
    uint8_t kill_size; /**< Length of the kill buffer. */
#endif

#ifdef CONFIG_MODULE_RDLINE_HISTORY
    /* history */
    struct cirbuf history;
    char history_buf[RDLINE_HISTORY_BUF_SIZE];
    int8_t history_cur_line;
#endif

    /* callbacks and func pointers */
    rdline_write_char_t *write_char; /**< Write char callback. */
    rdline_validate_t *validate; /**< Validate buffer callback. Called after a press on enter. */
    rdline_complete_t *complete; /**< Complete buffer callback. Called after a press on tab. */

    /* vt100 parser */
    struct vt100 vt100; /**< VT-100 associated with the buffer, for arrows, <C-A>, etc... */
};

/**
 * Init fields for a struct rdline. Call this only once at the beginning
 * of your program.
 * \param rdl A pointer to an uninitialized struct rdline
 * \param write_char The function used by the function to write a character
 * \param validate A pointer to the function to execute when the
 *                 user validates the buffer.
 * \param complete A pointer to the function to execute when the
 *                 user completes the buffer.
 */
void rdline_init(struct rdline *rdl,
         rdline_write_char_t *write_char,
         rdline_validate_t *validate,
         rdline_complete_t *complete);


/**
 * Init the current buffer, and display a prompt.
 * \param rdl A pointer to a struct rdline
 * \param prompt A string containing the prompt
 */
void rdline_newline(struct rdline *rdl, const char *prompt);

/**
 * Call it and all received chars will be ignored.
 * \param rdl A pointer to a struct rdline
 */
void rdline_stop(struct rdline *rdl);

/**
 * Restart after a call to rdline_stop()
 * \param rdl A pointer to a struct rdline
 */
void rdline_restart(struct rdline *rdl);

/**
 * Redisplay the current buffer
 * \param rdl A pointer to a struct rdline
 */
void rdline_redisplay(struct rdline *rdl);


/**
 * append a char to the readline buffer.
 * @return 1 when the line has been validated.
 * @return 2 when the user asked to complete the buffer.
 * @return -1 if it is not running.
 * @return -2 if EOF (ctrl-d on an empty line).
 * @return 0 in every other case.
 * @todo error case when the buffer is full ?
 *
 * \param rdl A pointer to a struct rdline
 * \param c The character to append
 */
int8_t rdline_char_in(struct rdline * rdl, char c);

/**
 * Return the current buffer, terminated by '\0'.
 * \param rdl A pointer to a struct rdline
 * @returns A pointer to the current buffer.
 */
const char *rdline_get_buffer(struct rdline *rdl);


/**
 * Add the buffer to history.
 * @return < 0 on error.
 * \param rdl A pointer to a struct rdline
 * \param buf A buffer that is terminated by '\0'
 */
int8_t rdline_add_history(struct rdline *rdl, const char *buf);

/**
 * Clear current history
 * \param rdl A pointer to a struct rdline
 */
void rdline_clear_history(struct rdline *rdl);

/**
 * Get the i-th history item
 * @returns a pointer to the i-th element in the history.
 * @param rdl A pointer to a struct rdline
 * @param i The index of the history element to get
 */
char *rdline_get_history_item(struct rdline *rdl, uint8_t i);

#endif /* _RDLINE_H_ */
