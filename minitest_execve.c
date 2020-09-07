#include <unistd.h>
#include <stdio.h>

int main ()
{ 
    char *argv[]={"ls", "-l", NULL};
    char *env[]={"PATH=/Library/Frameworks/Python.framework/Versions/3.7/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/MacGPG2/bin:/Library/Frameworks/Python.framework",NULL};
    pid_t pid;

    if((pid = fork()) == -1)
        printf("fork error");
    else if (pid == 0)
    {
    if(execve("/bin/ls",argv,env) == -1) // toujours bien mettre la path exacte /bin/ls en arg1 (filename)
        printf("not ok\n");
    return 0;
    }
}