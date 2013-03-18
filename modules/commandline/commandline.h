#ifndef _COMMANDLINE_H_
#define _COMMANDLINE_H_


/** @typedef command_t
 *
 * A single command in the commandline module, could be though as a single
 * shell utility.
 */
typedef struct {
    void (*f)(int, char **); /** The function itself, taking argc & argv as parameters. */
    char name[40]; /**< The name of the function, aka argv[0]. */
} command_t;

/** Inits the command line interface. 
 * @param [in] c An array containing all the commands, finished by a command
 * with NULL as f.
 * */
void commandline_init(command_t *c);

/** Inputs a char to the command line interface.
 *
 * This functions adds a character to the command line interface it is typically
 * called from a UART receive interrupt.
 *
 * @note commandline_init() must have been called before any call to this function.
 */
void commandline_input_char(char c);


#define COMMAND(n, fu) {.name = (n), .f = (void (*)(int, char **))(fu)}

#endif
