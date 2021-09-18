/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 18:26:12 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# define DOUBLE_QUOT	34
# define SINGLE_QUOT 39
# define NEUTRAL_MODE 100
# define SINGLE_MODE 101
# define DOUBLE_MODE 102
# define BUFF_SIZE 4096
# define STATUS_CMD_NOT_FOUND 127
# define STATUS_CMD_NOT_EXECUTABLE 126
# define IN 1
# define OUT 0

typedef struct stat			t_stat;
typedef struct s_token		t_token;
typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;

typedef enum e_cmd_type
{
	ABSOLUTE,
	RELATIVE,
	COMMAND
}			t_cmd_type;

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_tokentype{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_TAB = '\t',
	CHAR_NULL = 0,
	CHAR_EMPTY = -5,
	DOUBLE_GREATER = -4,
	DOUBLE_LESSER = -3,
	IO_NUMBER = -2,
}			t_token_type;

struct s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*data;
	size_t			space_len;
};

typedef struct s_lexer
{
	int				i;
	int				word_len;
	char			quote_status;
	char			*str;
	size_t			space_len;
	t_token_type	token_type;
}				t_lexer;

struct		s_redir
{
	int			backup_fd;
	int			left_fd;
	int			right_fd;
	int			type;
	int			is_quot;
	char		*open_filepath;
	t_redir		*next;
	t_redir		*prev;
};

struct			s_cmd
{
	t_token			*args;
	int				argc;
	struct s_cmd	*next;
	struct s_redir	*redirect;
	int				final_greater_fd;
	int				final_lesser_fd;
	pid_t			pid;
};

typedef enum e_token_state
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_GENERAL,
}			t_token_state;

typedef struct s_env
{
	char			*key;
	char			*value;
	t_bool			is_env;
	struct s_env	*next;
}			t_env;

typedef enum e_pipe_state
{
	NO_PIPE,
	READ_ONLY,
	WRITE_ONLY,
	READ_WRITE
}			t_pipe_state;

typedef struct s_mshl_data
{
	int				argc;
	char			**argv;
	t_env			*envs;
	int				exit_status;
	t_pipe_state	pipe_state;
	int				pipe[2];
	t_bool			interrupted;
	char			*command;
}			t_mshl_data;

/* mshl_data */
t_mshl_data	*ft_mshl_data_init(t_env *envs, char *argv[]);
void		ft_mshl_data_destroy(void);

/* exec functions */
void		ft_exec_commands(t_cmd *cmd);
t_bool		ft_exec_command(t_cmd *cmd, int old_pipe[]);
void		ft_wait_process(t_cmd *cmd);
void		ft_exec_child_process(int new_pipe[], int old_pipe[], t_cmd *cmd);
void		ft_exec_parent_process(int new_pipe[], int old_pipe[], t_cmd *cmd,
				pid_t pid);
int			ft_exec_builtin(t_cmd *cmd);
t_bool		ft_is_builtin_command(char *str);

/* lexer functions */
void		set_token_redirects(t_lexer *lx);
void		set_token_quotes(t_lexer *lx);
void		set_token_digits(t_lexer *lx);
void		set_token_spaces(t_lexer *lx);
void		set_token_general(t_lexer *lx);
t_token		*ft_lexer(char *str);

/* Common functions */
void		ft_error(char *command, char *message, int exit_status);
void		ft_free_char(char **target);
void		ft_safe_free_split(char ***target);
void		ft_error_display(char *command, char *message, int exit_status);
char		*ft_join_path(const char *prev, const char *next);
t_bool		ft_min(int x, int y);
t_bool		ft_max(int x, int y);

/* Token functions */
t_token		*ft_token_create(char *data, t_token_type type);
void		ft_token_add(t_token *new_token, t_token **tokens);
void		ft_token_print(t_token *tokens);
int			ft_token_length(t_token *tokens);
char		**ft_token_array(t_token *tokens, int start, int len);
char		*ft_token_str(t_token *tokens, int start, int len);
void		ft_token_destroy(t_token *token, t_token **tokens);
void		ft_token_free(t_token *tokens);
t_token		*ft_token_get_first(t_token *tokens);
t_token		*ft_token_get_last(t_token *tokens);
void		ft_token_destroy_all(t_token **tokens);

/* Environ functions */
t_env		*ft_env_init(char **environ);
t_env		*ft_env_create(char *str);
void		ft_env_add(t_env *new_env, t_env **envs);
t_env		*ft_env_dup(t_env *env);
void		ft_env_destroy(char *key);
void		ft_env_destroy_all(t_env *env);
t_env		*ft_env_get(const char *key, t_env *envs);
void		ft_env_update(const char *key, const char *value);
char		**ft_env_str_array(t_env *envs);
t_env		**ft_env_array(t_env *envs);
t_bool		ft_env_is_valid_key(char *key);
t_env		**ft_env_sort(void);
size_t		ft_env_len(t_env *envs);

/* Expansion functions */
void		ft_expand_cmd_utils(t_token *t, char **str);
void		ft_expand_cmd(t_cmd *cmd);
void		ft_expand_str(char **str);

/* Env functions */
int			ft_env(void);

/* Unset functions */
int			ft_unset(t_cmd *cmd);

/* Export functions */
int			ft_export_print_envs(void);
int			ft_export_set_envs(t_cmd *cmd);
int			ft_export(t_cmd *cmd);

/* exit function */
int			ft_exit(t_cmd *cmd);
t_bool		ft_is_strdigit(char *str);
int			ft_strcmp(const char *s1, const char *s2);
t_bool		ft_error_exit(char *massage);
void		ft_error_num(t_cmd *cmd);

/* cd function */
int			ft_cd(t_cmd *cmd);
t_bool		ft_is_tilde(t_cmd *cmd);
int			ft_isnot_path(t_mshl_data *g_mshl_data, char *pwd);
t_bool		ft_error_cd(char *file);
void		ft_check_dup_str(char **split_path);
void		ft_skip_dot(char **split_path, size_t i,
				size_t *dot_count, int flag);
char		**ft_skip_and_count_dot(char **split_path, size_t *dot_count,
				size_t *dot_dot_count);
char		*ft_convert_path(char **split_path);

/* pwd function */
int			ft_pwd(void);

/* echo function */
int			ft_echo(t_cmd *cmd);

/* parser function */
t_cmd		*ft_parser(t_token *token, t_cmd *cmd);
t_cmd		*ft_cmd_lstnew(void);
t_token		*create_token(void);
t_token		*last_token(t_token *token);
void		add_token(t_token *copy);

/* error function */
t_bool		ft_validate_str(char *str);
t_bool		ft_isalnum_str(char *str);
t_bool		ft_check_quot(char *str);
t_bool		ft_validate_token(t_token *tokens);

/* get command path function */
char		*ft_cmd_path_search_binary(const char *cmd);
char		**ft_cmd_path_get_colon(const char *str, const char *default_value);
char		*ft_cmd_path(const char *cmd);

/* pipe functions */
void		ft_pipe_duplicate(t_pipe_state state, int old_pipe[],
				int new_pipe[]);
void		ft_pipe_update(t_pipe_state state, int old_pipe[], int new_pipe[]);
void		ft_pipe_update_state(t_cmd *command);
void		ft_pipe_destroy(int pipes[]);

/* sigint functions */
void		ft_sigint_handler(int sig);
void		ft_sigint_setter(void (*func)(int));

/* redirect functions */
t_redir		*ft_create_redirect(void);
t_bool		ft_setup_redirect(t_cmd	*cmd);
void		ft_test_print_redirect(t_cmd *cmd);
void		ft_import_redirect_information(t_cmd *cmd, t_token *redirect_token,
				int default_fd, t_bool status);
t_bool		ft_dup_heredoc(t_redir *redir, t_cmd *cmd);
t_bool		ft_getfd_redirect(t_cmd *cmd);
t_bool		ft_check_redirect(t_cmd *cmd);
t_bool		ft_dup_redirect(t_cmd *cmd, int	is_parent);
t_bool		ft_backup_fd(t_cmd *cmd);
t_bool		ft_delete_tmpfile(t_cmd *cmd, int final_greater_fd);
void		ft_redirect_token_destory(t_cmd *cmd, t_token *redirect_token);
t_bool		check_is_tokenfirst(t_token *redirect_token);

/* cmd functions */
void	ft_cmd_destroy(t_cmd *cmd);


#	endif
