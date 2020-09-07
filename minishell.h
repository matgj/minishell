#ifndef MINISHELL_H
# define MINISHELL_H 

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

#define BUFFER_SIZE 1024
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// pour rendre dup2 plus clairs dans lexecution : 
// # define IN				1
// # define OUT			0
//if (dup2(cmdl->fd[IN], STDOUT_FILENO) == ERROR)
//				syscall_error_in_child();
//if (cmdl->prev && cmdl->prev->type == '|')
//		{
//			if (dup2(cmdl->prev->fd[OUT], STDIN_FILENO) == ERROR)
//				syscall_error_in_child();

typedef struct  s_shell
{
	int		status; //variable retournee par la fonction execute pour savoir quand quitter
	char 	**var_env; //liste des variables d'environnement

}		t_shell;

typedef	struct	s_cmds  // structure contenant toutes les infos d'une commande
{
	char	*cast;  //variable qui sert a eviter une erreur de compil avec un while sur cmds_pipe[i]
	char	*path; //path exacte de l'exe.
	char	**arg; //tokens a executes retournees par split pipes et split semi, fini par NULL
}				t_cmds;

t_shell g_shell;

void	execute();
int     exit_success(void);
int     exit_failure(void);
void    free_var(void);
void	parsing(char *line);
void    command_creation(t_cmds cmds);

char	**env_import(char **envp);


char 	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);

int 	get_next_line(int fd, char **buf);
char	*ft_cpy_line(char *s);
int		ft_check_bn(char *str);
#endif
