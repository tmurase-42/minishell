UNAME	:= $(shell uname)
NAME	= minishell
FILES	= main.c \
		lexer/ft_lexer.c lexer/ft_lexer_utils.c\
		exec/ft_exec_commands.c exec/ft_wait_process.c exec/ft_exec_child_process.c exec/ft_exec_builtin.c \
		exec/ft_is_builtin_command.c exec/ft_exec_parent_process.c exec/ft_exec_command.c \
		environ/ft_env_add.c environ/ft_env_destroy.c environ/ft_env_get.c environ/ft_env_create.c \
		environ/ft_env_init.c environ/ft_env_update.c environ/ft_env_array.c environ/ft_env_is_valid_key.c \
		environ/ft_env_dup.c environ/ft_env_sort.c environ/ft_env_destroy_all.c environ/ft_env_str_array.c \
		environ/ft_env_len.c \
		exit/ft_exit.c  exit/ft_exit_utils.c \
		common/common.c common/ft_join_path.c common/min_max.c \
		env/ft_env.c \
		export/ft_export_set_envs.c export/ft_export.c export/ft_export_print_envs.c \
		unset/ft_unset.c \
		cd/ft_cd.c  cd/ft_cd_utils.c cd/ft_cd_utils_2.c \
		expansion/ft_expand_cmd_utils.c expansion/ft_expand_cmd.c expansion/ft_expand_str.c \
		pwd/ft_pwd.c \
		parser/parser.c parser/parser_utils.c\
		echo/ft_echo.c \
		validates/ft_validate_token.c validates/ft_validate_token_2.c validates/ft_validate_str.c \
		tokens/ft_token_add.c tokens/ft_token_create.c  tokens/ft_token_print.c tokens/ft_token_length.c \
		tokens/ft_token_array.c tokens/ft_token_free.c tokens/ft_token_str.c tokens/ft_token_destroy.c \
		tokens/ft_token_get_first.c tokens/ft_token_get_last.c \
		cmd_path/ft_cmd_path.c cmd_path/ft_cmd_path_search_binary.c cmd_path/ft_cmd_path_get_colon.c \
		pipe/ft_pipe_update.c pipe/ft_pipe_duplicate.c pipe/ft_pipe_update_state.c pipe/ft_pipe_destroy.c \
		sigint/ft_sigint_handler.c sigint/ft_sigint_setter.c \
		redirect/ft_redirect_setup.c redirect/ft_dup_redirect.c redirect/ft_heredoc.c redirect/ft_getfd_redirect.c redirect/ft_import_redirect_infor.c \
		redirect/ft_check_redirect.c

SRCS		= $(addprefix $(SDIR), $(FILES))
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror
CPPFLAGS	= -I $(shell brew --prefix readline)/include
LDFLAGS 	= -lreadline -L $(shell brew --prefix readline)/lib
RM			= rm -f
NAME_LEAKS	:= minishell_leaks
SRCS_LEAKS	:= leaks.c

ifdef LEAKS
NAME		:= $(NAME_LEAKS)
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) ./libft/libft.a -o $(NAME)
	echo > ~/.inputrc set echo-control-characters off

clean:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./libft fclean
	$(RM) $(NAME) minishell
	$(RM) $(NAME) minishell_leaks

re: fclean all

leaks	:
	$(MAKE) CFLAGS="$(CFLAGS) -D LEAKS=1" SRCS="$(SRCS) $(SRCS_LEAKS)" LEAKS=TRUE

.PHONY: all fclean clean re
