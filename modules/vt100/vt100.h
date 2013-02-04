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
 *  Revision : $Id: vt100.h,v 1.1.2.2 2009-04-07 20:01:16 zer0 Exp $
 *
 *
 */

/** @file vt100.h
 *
 * @brief Interface to the VT100 parser.
 *
 * This modules implements VT100 style escape sequence, both for sending them
 * and interpreting them.
 */

#ifndef _VT100_H_
#define _VT100_H_

/** VT100 Bell escape sequence. */ 
#define vt100_bell         "\007"

/** VT100 Backspace escape sequence. */
#define vt100_bs           "\010"

/** VT1oo Clear sequence. */
#define vt100_bs_clear     "\010 \010"

/** VT100 Tab sequence. */
#define vt100_tab          "\011"

/** VT100 Carriage return and line feed sequence. */
#define vt100_crnl         "\012\015"

/** VT100 clear line from cursor right sequence. */
#define vt100_clear_right  "\033[0K"

/** VT100 clear line from cursor left sequence. */
#define vt100_clear_left   "\033[1K"

/** VT100 clear screen from cursor down sequence. */
#define vt100_clear_down   "\033[0J"

/** VT100 clear screen from cursor up sequence. */
#define vt100_clear_up     "\033[1J"

/** VT100 clear entire line sequence. */
#define vt100_clear_line   "\033[2K"

/** VT100 clear entire screen sequence. */
#define vt100_clear_screen "\033[2J"

/** VT100 Up arrow pressed sequence. */
#define vt100_up_arr       "\033\133\101"

/** VT100 Down arrow pressed sequence. */
#define vt100_down_arr     "\033\133\102"

/** VT100 right arrow pressed sequence . */
#define vt100_right_arr    "\033\133\103"

/** VT100 Left arrow pressed sequence. */
#define vt100_left_arr     "\033\133\104"

/** VT100 multiple move right sequence. */
#define vt100_multi_right  "\033\133%uC"

/** VT100 multiple move left sequence. */
#define vt100_multi_left   "\033\133%uD"

/** VT100 Suppr key sequence. */
#define vt100_suppr        "\033\133\063\176"

/** VT100 home key pressed sequence. */
#define vt100_home         "\033M\033E"

/** VT100 word left sequence. */
#define vt100_word_left    "\033\142"

/** VT100 word right sequence. */
#define vt100_word_right   "\033\146"

/* Result of parsing : it must be synchronized with vt100_commands[]
 * in vt100.c */
#define KEY_UP_ARR 0        /**< Result of parsing if up arrow was pressed. */
#define KEY_DOWN_ARR 1      /**< Result of parsing if down arrow was pressed. */
#define KEY_RIGHT_ARR 2     /**< Result of parsing if right arrow was pressed. */ 
#define KEY_LEFT_ARR 3      /**< Result of parsing if left arrow was pressed. */
#define KEY_BKSPACE 4       /**< Result of parsing if backspace was pressed. */
#define KEY_RETURN 5        /**< Result of parsing if return was pressed. */
#define KEY_CTRL_A 6        /**< Result of parsing if Ctrl+A was pressed. */
#define KEY_CTRL_E 7        /**< Result of parsing if Ctrl+E was pressed. */
#define KEY_CTRL_K 8        /**< Result of parsing if Ctrl+K was pressed. */
#define KEY_CTRL_Y 9        /**< Result of parsing if Ctrl+Y was pressed. */
#define KEY_CTRL_C 10       /**< Result of parsing if Ctrl+C was pressed. */
#define KEY_CTRL_F 11       /**< Result of parsing if Ctrl+F was pressed. */
#define KEY_CTRL_B 12       /**< Result of parsing if Ctrl+B was pressed. */
#define KEY_SUPPR 13        /**< Result of parsing if Suppr was pressed. */
#define KEY_TAB 14          /**< Result of parsing if tab was pressed. */
#define KEY_CTRL_D 15       /**< Result of parsing if Ctrl+D was pressed. */
#define KEY_CTRL_L 16       /**< Result of parsing if Ctrl+L was pressed. */
#define KEY_RETURN2 17      /**< Result of parsing if Return 2 (?) was pressed. */
#define KEY_META_BKSPACE 18 /**< Result of parsing if Meta+Backspace was pressed. */
#define KEY_WLEFT 19        /**< Result of parsing if word left was pressed. */
#define KEY_WRIGHT 20       /**< Result of parsing if word right was pressed. */
#define KEY_HELP 21         /**< Result of parsing if Help key ("?") was pressed. */

/** This array stores all the parsable keyboard commands. */
extern const char* vt100_commands[];

/** The possible parser states. */
enum vt100_parser_state {
	VT100_INIT,         /**< Default state, no command arrived. */
	VT100_ESCAPE,       /**< Escape sequence, after ESC arrived. */
	VT100_ESCAPE_CSI,   /**< Extended escape sequences. */
};

/** Size of the VT100 parser buffer. */
#define VT100_BUF_SIZE 8

/** VT100 parser instance. */
struct vt100 {
	int bufpos; /**< Position in the buffer. */
	char buf[VT100_BUF_SIZE]; /**< Reception buffer. */
	enum vt100_parser_state state; /**< Parser state. */
};

/** Init of a VT100 parser. 
 *
 * @param [in] vt The VT100 instance to init.
 */
void vt100_init(struct vt100 *vt);

/** Input a new character. 
 * @param [in] vt The VT100 parser instance.
 * @param [in] c The character to input.
 * @return -1 if the character is not part of a control sequence
 * @return -2 if c is not the last char of a control sequence
 * @return Else the index in vt100_commands[]
 */
int vt100_parser(struct vt100 *vt, unsigned char c);

#endif
