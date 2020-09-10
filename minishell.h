#ifndef MINISHELL_H
# define MINISHELL_H 

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>

#define BUFFER_SIZE 1024
#define EXIT_SUCCESS 0 //false = bool 0
#define EXIT_FAILURE 1 //true = bool 1

#define ARG_MAX 262144 // ou peut etre autre ? ou ca 131072

// astuce pour rendre dup2 plus clairs dans lexecution : 
// # define IN				1
// # define OUT			0
//if (dup2(cmdl->fd[IN], STDOUT_FILENO) == ERROR)
//				syscall_error_in_child();
//if (cmdl->prev && cmdl->prev->type == '|')
//		{
//			if (dup2(cmdl->prev->fd[OUT], STDIN_FILENO) == ERROR)
//				syscall_error_in_child();

typedef struct  s_shell //structure contenant les variables d environnement et le status
{
	int		status; //variable retournee par la fonction execute pour savoir quand quitter le minishell;
	char	**envp; //liste des variables d'environnement "pointer to a null-terminated array of character pointers to null-terminated strings.  A pointer to this array is normally stored in the global variable environ. These strings pass information to the new process that is not directly an argument to the command "
}		t_shell;

typedef	struct	s_cmds  // structure contenant toutes les infos d'une commande
{
	char	*name;   //nom de la commande recupere via argv
	char	*path;   //path exacte de l'executable
	char	**argv;  //pointeur sur tableau de pointeur sur tokens a executes retournees par split pipes et split semi, fini par NULL. "pointer to a null-terminated array of character pointers to null-terminated character strings.  These strings construct the argument list to be made available to the new process.  At least one argument must be present in the array; by custom, the first element should be the name of the executed program (for example, the last component of path)."
	int 	chevron; //> = redirec stdin (0) < = redic stout (1); 2 >> 3 = rien
	int		argc;    // nombre darguments dune commande (ls -l = deux arguments, wc -l > hello.txt = 4 argument)
	int 	*output; //tabl d'int pour les files descriptor d'une commande qui va rediriger son ouput
	int		input;   //fd qui sert dinput a une commande
}				t_cmds;

t_cmds g_cmds;  //permet de rendre global la structure et de pas se faire chier a passer les variables en parametres;
t_shell g_shell;

char 	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);

int 	get_next_line(int fd, char **buf);
char	*ft_cpy_line(char *s);
int		ft_check_bn(char *str);

void	execute();
int     exit_success(void);
int     exit_failure(void);
void    free_var(void);
void	parsing(char *line);
void    command_management(t_cmds *cmds);
void	redirection(t_cmds *cmds);
void    ft_tab_output(int *tab_fds, int fd);

char	**env_import(char **envp);
char	*command_path(t_cmds *cmds);


void     test_cmd(t_cmds cmds);
void     test_env(t_cmds *cmds);

void    ft_echo(t_cmds cmds);
void    ft_cd(t_cmds cmds);
void    ft_pwd(t_cmds cmds);
void    ft_export(t_cmds cmds);
void    ft_unset(t_cmds cmds);
void    ft_env(t_cmds cmds);
void    ft_exit(t_cmds cmds);

#endif
