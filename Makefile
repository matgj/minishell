NAME = minishell

FLAGS = -Wall -Werror -Wextra -fsanitize=address -fsanitize=address

INCLUDE = -I minishell.h

SRCS =	main.c execute.c exit.c parsing.c env.c \
		utils/ft_memmove.c utils/ft_strdup.c utils/ft_strjoin.c \
		utils/ft_strlen.c utils/get_next_line_utils.c utils/get_next_line.c utils/ft_split.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS) 
			@rm -rf minishell
			@gcc -o $(NAME) $(INCLUDE) $(OBJS) $(FLAGS)
	
all : $(NAME)

clean :
		rm -f $(OBJS)
		
fclean : clean
		rm -f $(NAME)
		
re : fclean all