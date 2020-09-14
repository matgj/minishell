#include "minishell.h"

//A common use of pipes is to send data to or receive data 
//from a program being run as a subprocess. 
//One way of doing this is by using a combination of 
//pipe (to create the pipe), fork (to create the subprocess),
//dup2 (to force the subprocess to use the pipe as its standard 
//input or output channel), and exec (to execute the new program). 

void    execute(char **line)
{
    printf("line:%s\n", *line);
    g_shell.status = 1;
}