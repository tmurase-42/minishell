UNAME    := $(shell uname)
NAME            = minishell
FILES           = main.c get_next_line.c get_next_line_utils.c ft_lexer.c exec/ft_execute_command.c \
									environ/ft_env_add.c environ/ft_env_delete.c environ/ft_env_get.c environ/ft_env_create.c\
									environ/ft_env_init.c environ/ft_env_update.c \
									exit/ft_exit.c \
									common/common.c \
									env/ft_env.c \
									export/ft_export.c \
									unset/ft_unset.c \
									cd/ft_cd.c \
									expansion/ft_expand.c \
									pwd/ft_pwd.c \
									parser/parser.c \
									tokens/ft_token_add.c tokens/ft_token_create.c  tokens/ft_token_print.c tokens/ft_token_length.c tokens/ft_token_array.c \

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
