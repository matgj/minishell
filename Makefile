NAME = minishell

FLAGS = -Wall -Werror -Wextra -fsanitize=address

INCLUDE = -I minishell.h

SRCS =	main.c exit.c parsing.c parsing2.c parsing3.c parsing4.c parsing5.c parsing6.c environment.c command.c test.c \
		parsing_utils.c command2.c command3.c signals.c command_utils.c command_error.c status.c \
		utils/ft_calloc.c utils/ft_bzero.c utils/ft_memmove.c utils/ft_strdup.c  utils/ft_strcat.c utils/ft_strjoin.c utils/ft_strcmp.c \
		utils/ft_strlen.c utils/get_next_line_utils.c utils/get_next_line.c utils/ft_split.c utils/ft_itoa.c utils/ft_strncmp.c \
		utils/ft_substr.c utils/ft_printf.c utils/ft_display.c utils/ft_conv_cspm.c utils/ft_conv_diux.c utils/ft_flags_basic.c \
		utils/ft_flags_cspm.c utils/ft_parse_flags.c utils/ft_printf_utils.c utils/mmalloc.c utils/ft_atoi.c \
		builtins/ft_echo.c builtins/ft_pwd.c builtins/ft_env.c builtins/ft_cd.c builtins/export/ft_export.c \
		builtins/export/ft_export_utils_0.c builtins/export/ft_export_utils_1.c builtins/ft_unset.c \
		builtins/utils/ft_memset.c builtins/utils/ft_putendl_fd.c builtins/utils/ft_putstr_fd.c builtins/ft_exit.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
			@rm -rf minishell
			@gcc -o $(NAME) $(INCLUDE) $(OBJS) $(FLAGS)

all : $(NAME)

clang : $(OBJS)
	@clang -o $(NAME) $(INCLUDE) $(OBJS) -g

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : fclean all
