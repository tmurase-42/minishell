UNAME    := $(shell uname)
NAME            = minishell
FILES           = main.c get_next_line.c get_next_line_utils.c perse_command.c
SRCS        = $(addprefix $(SDIR), $(FILES))
OBJS        = $(SRCS:.c=.o)
CC              = gcc
CFLAGS      = -g -Wall -Wextra -Werror 
RM              = rm -f


all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(OBJS) $(CFLAGS)  ./libft/libft.a -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./libft fclean
	$(RM) $(NAME) minishell

re: fclean all

.PHONY: all fclean clean re
