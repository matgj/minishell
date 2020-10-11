NAME = minishell

FLAGS = -Wall -Werror -Wextra -fsanitize=address -fsanitize=address

INCLUDE = -I minishell.h

SRCS =	main.c builtins.c exit.c parsing.c parsing2.c parsing3.c parsing4.c parsing5.c environment.c command.c test.c \
		parsing_utils.c command2.c signals.c \
		utils/ft_calloc.c utils/ft_bzero.c utils/ft_memmove.c utils/ft_strdup.c utils/ft_strjoin.c utils/ft_strcmp.c \
		utils/ft_strlen.c utils/get_next_line_utils.c utils/get_next_line.c utils/ft_split.c utils/ft_strncmp.c \
		utils/ft_substr.c utils/ft_printf.c utils/ft_display.c utils/ft_conv_cspm.c utils/ft_conv_diux.c utils/ft_flags_basic.c \
		utils/ft_flags_cspm.c utils/ft_parse_flags.c utils/ft_printf_utils.c \

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
