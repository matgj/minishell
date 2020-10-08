/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitest_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:50:09 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/08 16:24:57 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main ()
{ 
    char *argv[]={"ls", "-l", NULL};
    char *env[]={"PATH=/Library/Frameworks/Python.framework/Versions/3.7/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/MacGPG2/bin:/Library/Frameworks/Python.framework",NULL};
    pid_t pid;

    if((pid = fork()) == -1)
        ft_printf("fork error");
    else if (pid == 0)
    {
    if(execve("/bin/ls",argv,env) == -1)
        ft_printf("not ok\n");
    return 0;
    }
}