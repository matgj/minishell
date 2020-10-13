/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:51:31 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/13 21:04:34 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdarg.h>
# include <string.h>

# define BUFFER_SIZE 1024
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define STDOUT 1
# define STDIN 0
# define PIPE 5
# define SEMI 2
# define R_OUT 7
# define R_IN 8
# define VAR 4
# define REPLACED 3
# define BS 7
# define A 6
# define BS_Q 16
# define SPACE 1
# define ARG_MAX 262144

typedef struct		s_printf
{
	char	flag;
	int		wid;
	int		prec;
	char	type;
	int		fd;

}					t_printf;

typedef struct		s_shell
{
	int		dquotes;
	int		status;
	char	**envp;
	int		redir;
	pid_t	pid;
	char	*var_env;
}					t_shell;

typedef	struct		s_cmds
{
	char	*name;
	char	*path;
	char	**argv;
	int		chevron;
	int		argc;
	int		output[ARG_MAX];
	int		input;
}					t_cmds;

t_cmds		g_cmds;
t_shell		g_shell;
t_printf	g_printf;

char				*ft_strdup(const char *str);
size_t				ft_strlen(const char *str);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split(char const *s, char c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					get_next_line(int fd, char **buf);
char				*ft_cpy_line(char *s);
int					ft_check_bn(char *str);

void				ft_putchar(char c, int *res);
void				ft_putstr(char *src, int *res);
int					ft_printf(const char *src, ...);
int					ft_atoi_mini(const char *src, int *i);
char				*ft_itoa_base(long int nb, int base, char *base_tab);
void				ft_c(va_list arg_list, t_printf *conv, int *res);
void				ft_s(va_list arg_list, t_printf *conv, int *res);
void				ft_mod(t_printf *conv, int *res);
void				ft_di(va_list arg_list, t_printf *conv,
	int *res, char *base_tab);
void				ft_u(va_list arg_list, t_printf *conv,
	int *res, char *base_tab);
void				ft_x(va_list arg_list, t_printf *conv,
	int *res, char *base_tab);
void				ft_p(va_list arg_list, t_printf *conv,
	int *res, char *base_tab);
void				ft_zero(t_printf *conv, char *src, int *res, int s_len);
void				ft_minus(t_printf *conv, char *src, int *res, int s_len);
void				ft_spaces(t_printf *conv, char *src, int *res, int s_len);
void				ft_space_s(t_printf *conv, char *str, int *res, int len);
void				ft_zero_s(t_printf *conv, char *str,
int *res, int len);
void				ft_minus_s(t_printf *conv, char *str,
int *res, int len);
void				ft_flags_prec(const char *src, int *i,
	va_list arg_list, t_printf *conv);
void				ft_flags_wid(const char *src, int *i,
	va_list arg_list, t_printf *conv);
void				ft_flags_zero_minus(const char *src,
	int *i, t_printf *conv);
void				ft_flag_p(t_printf *conv, char *str, int *res, int len);
int					ft_check_type(char c);

void				ft_cpy_var(char *str);
int					ft_alphanum(char c);
char				*dol_create(void);
void				read_line(char **line);
void				parsing(char *line);
void				parse_token(char ***token, char *cmds_pipe);
void				command_creation(t_cmds *cmds);
void				cmd_last_arg(t_cmds *cmds);
void				command_management(t_cmds *cmds);
int					command_type_child(t_cmds cmds);
int					command_type_parent(t_cmds cmds);
int					command_exec(t_cmds cmds);
void				command_clean(t_cmds *cmds);
char				*join_splits(char **tabs);
void				redirection(t_cmds *cmds);
void				ft_tab_output(int *tab_fds, int fd);
void				command_plug(t_cmds *cmds);
void				command_exec2();
void				quotes(char *line);
void				insert_actions(char *s);
void				double_quotes(char *c, int *q, int *dq);
void				simple_quotes(char *c, int *q, int *dq);
char				*var_env(char *line);
void				check_pid(void);
void				signals(void);
void				exit_shell(int status, int newline);
void				free_split(char **tabs);
int					syntax_error(char *line);
int					syntax_err2(char *line, int i, char c);
void				print_syntax_err(char *line);
int					empty(char *line);
void				close_fds(t_cmds *cmds);
void				free_struct(t_cmds cmds);

char				**env_import(char **envp);
char				*command_path(t_cmds *cmds);

void				test_cmd(t_cmds cmds);
void				test_env(t_cmds *cmds);
void				test_tab_cmds(t_cmds *cmds, int i);

void				ft_echo(t_cmds cmds);
void				ft_cd(t_cmds cmds);
void				ft_pwd(t_cmds cmds);
void				ft_export(t_cmds cmds);
void				ft_unset(t_cmds cmds);
void				ft_env(t_cmds cmds);
void				ft_exit(t_cmds cmds);

#endif
