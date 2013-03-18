#include <commandline.h>
#include <aversive.h>

#include <stdlib.h>
#include <rdline.h>
#include <string.h>

/* Behind this point it is not for user code. */
static void write_char(char c) {
    putchar(c);
}

/** The instance of the readline module used by the shell. */
static struct rdline rdl;

/** The prompt of the shell. */ 
static char prompt[] = "board>";

/* All the possibles delimiter for a token. */
#define DELIMITER " \n" 

static command_t *commands;

/** This function is called when user press enter. */
static void validate_buffer(const char *buf, int size) {
    int argc;
    unsigned int i;
    char **argv;

    char *buffer; /* we need our own non const copy of the buffer. */

    buffer = malloc(size);
    strncpy(buffer, buf, size);

    /* Counts all the tokens. */
    argc = 1;
    if(strtok(buffer, DELIMITER) == NULL)  /* empty line. */
        return;
    while(strtok(NULL, DELIMITER) != NULL)
        argc++;

    /* Needed because buffer was  modified by strtok. */
    strncpy(buffer, buf, size);

    /* Allocates memory for all the tokens objects. */
    argv = malloc(sizeof(char *) * argc);
    argv[0] = strtok(buffer, DELIMITER);

    /* Fills all the tokens. */
    for(i=1; i < (unsigned int)argc;i++) {
        argv[i] = strtok(NULL, DELIMITER);
    }

    /* Iterate over all commands. */
    for(i=0;commands[i].f != NULL;i++) {
        if(!strcmp(commands[i].name, argv[0])) {
            /* Run the command then exit. */
            commands[i].f(argc, argv);
            break;
        }
    }

    /* Checks if no matching command was found */
    if(commands[i].f == NULL) {
        printf("%s: command not found\n", argv[0]);
    }

    /* Cleanup. */
    free(argv);
    free(buffer);
}

/** This function is called each time the user press tab. */
static int complete_buffer(const char *buf, char *dst_buf, int dst_size, int *state) {
    printf("%s(%s;%p;%d;%d)\n", __FUNCTION__, buf, dst_buf, dst_size, *state);  

    return -2;
    /* TODO */ 
}

void commandline_input_char(char c) {
    int same;
    int ret;
    const char *buffer, *history;
    ret = rdline_char_in(&rdl, c);
    if (ret != 2 && ret != 0) {
        buffer = rdline_get_buffer(&rdl);
        history = rdline_get_history_item(&rdl, 0);
        if (history) {
            same = !memcmp(buffer, history, strlen(history)) &&
            buffer[strlen(history)] == '\n';
        }
        else
            same = 0;
        if (strlen(buffer) > 1 && !same)
            rdline_add_history(&rdl, buffer);
        rdline_newline(&rdl, prompt);
    }
}

void commandline_init(command_t c[]) {
    commands = c;
    rdline_init(&rdl, write_char, validate_buffer, complete_buffer);
    rdline_newline(&rdl, prompt);
}
