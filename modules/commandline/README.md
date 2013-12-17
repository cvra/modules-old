Commandline
===========

This module provides a shell which can be used to call functions, like a UNIX
shell. It will pass the arguments to the called functions using UNIX-like argc
and argv, which makes the writing of debug routines / utilities really quick and
easy.

Usage
-----

So let's say you want to write a simple debug routine that simply prints "Hello
world !", and the command should be called "hello". An example implementation of
such a program could be :

    void say_hi(void) {
        printf("Hello world !\n");
    }

The function then needs to be registered into an array of command which must be
terminated by a NULL command.

    command_t commands[] = {
        COMMAND("hello",say_hi);
        COMMAND("list_end", NULL);
    }

    commandline_init(commands);

Now we just need to feed the modules with the keyboard stream.

    while(1)
        commandline_input_char(getchar());

You now have a working shell with tab completion, emacs-like line editing,
etc...

Working with arguments
----------------------

The commandline modules support argument passing to the called routines. The
arguments are passed using argc and argv. You can find help about argc and argv
usage in any good C programming book. The only thing that changes to use
arguments is the function prototype (example below).

    void say_hi(int argc, char **argv) {
        int i;
        printf("Hello world !\n");
        printf("You passed me %d args.\n", argc);
        for(i=0; i<argc; i++)
            printf("argv[%d] = '%s'\n", i, argv[i]);
    }
