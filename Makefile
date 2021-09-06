UNAME    := $(shell uname)
NAME            = minishell
FILES           = main.c ft_lexer.c exec/ft_exec_commands.c exec/ft_wait_process.c exec/ft_exec_child_process.c exec/ft_exec_builtin.c exec/ft_is_builtin_command.c exec/ft_exec_parent_process.c \
									environ/ft_env_add.c environ/ft_env_delete.c environ/ft_env_get.c environ/ft_env_create.c \
									environ/ft_env_init.c environ/ft_env_update.c environ/ft_env_array.c \
									exit/ft_exit.c \
									common/common.c common/ft_join_path.c \
									env/ft_env.c \
									export/ft_export.c \
									unset/ft_unset.c \
									cd/ft_cd.c  cd/ft_cd_utils.c cd/ft_cd_utils_2.c \
									expansion/ft_expand.c \
									pwd/ft_pwd.c \
									parser/parser.c \
									echo/ft_echo.c \
									tokens/ft_token_error.c tokens/ft_token_error_2.c \
									tokens/ft_token_add.c tokens/ft_token_create.c  tokens/ft_token_print.c tokens/ft_token_length.c tokens/ft_token_array.c tokens/ft_token_free.c tokens/ft_token_str.c tokens/ft_token_destroy.c \
									cmd_path/ft_cmd_path.c cmd_path/ft_cmd_path_search_binary.c cmd_path/ft_cmd_path_get_colon.c \
									pipe/ft_pipe_update.c pipe/ft_pipe_duplicate.c pipe/ft_pipe_update_state.c pipe/ft_pipe_destroy.c \
									sigint/ft_sigint_handler.c sigint/ft_sigint_setter.c \
									redirect/ft_redirect_setup.c redirect/ft_dup_redirect.c

SRCS		= $(addprefix $(SDIR), $(FILES))
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror
CPPFLAGS	= -I $(shell brew --prefix readline)/include
LDFLAGS 	= -lreadline -L $(shell brew --prefix readline)/lib
RM			= rm -f


all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) ./libft/libft.a -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./libft fclean
	$(RM) $(NAME) minishell

re: fclean all

.PHONY: all fclean clean re
