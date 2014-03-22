#include <platform.h>
#include <commandline.h>

#include <stdio.h>
#include <stdlib.h>
#include <rdline.h>
#include <string.h>

/** This functions is used to write a char by the module. */
static void write_char(char c)
{
    putchar(c);
}

/** The instance of the readline module used by the shell. */
static struct rdline rdl;

/** The prompt of the shell. */
static char prompt[] = "board>";

/* All the possibles delimiter for a token. */
#define DELIMITER " \n"

/** List of all registered commands. */
static command_t *commands;

/** This function is called when user press enter. */
static void validate_buffer(const char *buf, int size)
{
    int argc;
    unsigned int i;
    char **argv;

    char *buffer;

    /* strtok() changes the buffer, so we copy it first. */
    buffer = malloc(size);
    strncpy(buffer, buf, size);

    /* Counts all the tokens. */
    argc = 1;
    if(strtok(buffer, DELIMITER) == NULL)  /* empty line. */
    {
        free(buffer);
        return;
    }

    while(strtok(NULL, DELIMITER) != NULL)
        argc++;

    /* Needed because buffer was  modified by strtok. */
    strncpy(buffer, buf, size);

    /* Allocates memory for all the tokens. */
    argv = malloc(sizeof(char *) * argc);
    argv[0] = strtok(buffer, DELIMITER);

    /* Gets all the tokens. */
    for(i=1; i < (unsigned int)argc;i++) {
        argv[i] = strtok(NULL, DELIMITER);
    }

    /* Iterate over all commands. */
    for(i=0;commands[i].f != NULL;i++) {
        /* If the command name matches. */
        if(!strcmp(commands[i].name, argv[0])) {
            /* Run the command then exit. */
            commands[i].f(argc, argv);
            break;
        }
    }

    /* Checks if no matching command was found. */
    if(commands[i].f == NULL) {
        printf("%s: command not found\n", argv[0]);
    }

    /* Cleanup. */
    free(argv);
    free(buffer);
}

/** This function is called each time the user press tab. */
static int complete_buffer(const char *buf, char *dst_buf, int dst_size, int *state)
{
    if(*state == 0){
        int size = strlen(buf);

        int i = size;
        while(buf[i-1] != ' ' && i > 0)
            i--;

        int j;
        int k;
        char* completed_cmd_name;

        for(j = 0; commands[j].f != NULL; j++) {
            for(k = i; k < size; k++) {
                if(buf[k] == commands[j].name[k-i])
                    completed_cmd_name = commands[j].name;
                else {
                    completed_cmd_name = NULL;
                    break;
                }
            }

            if(completed_cmd_name && (int)strlen(completed_cmd_name) - size + i < dst_size){
                strncpy(dst_buf, completed_cmd_name + (size - i), strlen(completed_cmd_name) - (size - i) + 1);
                int dst_string_size = strlen(dst_buf);
                dst_buf[dst_string_size] = ' ';
                dst_buf[dst_string_size + 1] = '\0';
                return 2;
            }
        }
    }

    return 0;
}

void commandline_input_char(char c)
{
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

void commandline_init(command_t c[])
{
    commands = c;
    rdline_init(&rdl, write_char, validate_buffer, complete_buffer);
    rdline_newline(&rdl, prompt);
}
