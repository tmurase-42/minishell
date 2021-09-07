/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/07 15:53:48 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>


#define DOUBLE_QUOT 34
#define SINGLE_QUOT 39
#define NEUTRAL_MODE 100
#define SINGLE_MODE 101
#define DOUBLE_MODE 102
#define BUFF_SIZE 4096

# define STATUS_CMD_NOT_FOUND 127
# define STATUS_CMD_NOT_EXECUTABLE 126

# define IN 1
# define OUT 0
# define MIN(x,y) (x < y ? x : y)
# define MAX(x,y) (x > y ? x : y)


typedef enum				e_cmd_type
{
	ABSOLUTE,
	RELATIVE,
	COMMAND
}							t_cmd_type;

typedef struct stat	t_stat;

typedef enum		e_bool
{
	FALSE,
	TRUE
}								t_bool;

typedef enum		e_node_kind
{
	ND_PIPE,
	ND_COMMAND
}					t_node_kind;

typedef struct		e_node
{
	t_node_kind kind;
	struct t_Node	*lefthand_side;
	struct t_Node	*righthand_side;
	struct s_cmd	*args;
}					t_node;

typedef enum	e_tokentype{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	//CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_TAB = '\t',
	CHAR_NULL = 0, // 深掘りすぎ。不要
	//D_SEMICOLON = -5, // 深掘りすぎ。不要
	CHAR_EMPTY = -5, //空文字
	DOUBLE_GREATER = -4, // >> ってこと。
	DOUBLE_LESSER = -3, // << ってこと。
	IO_NUMBER = -2, //謎
}				t_token_type;

typedef struct s_token	t_token;

struct			s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*data;
};

typedef struct s_redirect t_redirect;

struct 				s_redirect
{
	int		backup_fd;
	int		left_fd;
	int		right_fd;
	int		type;
	char	*open_filepath;
};

typedef struct s_cmd t_cmd;
struct			s_cmd
{
	t_token	*args;
	int		argc;
	struct	s_cmd *next;
	struct 	s_redirect *redirect;
	pid_t	pid;
};

typedef enum		e_token_state{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_GENERAL,
}								t_token_state;

typedef struct	s_env
{
	char			*key;
	char			*value;
	t_bool			is_env;
	struct s_env	*next;
}				t_env;

typedef struct s_history	t_history;
struct			s_history
{
	t_history	*next;
	t_history	*prev;
	char		*data;
	size_t		number;
};

typedef enum			e_pipe_state
{
	NO_PIPE,
	READ_ONLY,
	WRITE_ONLY,
	READ_WRITE
}						t_pipe_state;

typedef struct	s_mshl_data
{
	int				argc;
	char			**argv;
	t_env			*envs;
	int				exit_status;
	t_history		*histories;
	t_pipe_state	pipe_state;
	int				pipe[2];
	t_bool			interrupted;
}				t_mshl_data;

/* exec functions */
t_token	*ft_lexer(char *str);
void	ft_exec_commands(t_cmd *cmd);
void	ft_wait_process(t_cmd *cmd);
void	ft_exec_child_process(int new_pipe[], int old_pipe[], t_cmd *cmd);
void	ft_exec_parent_process(int new_pipe[], int old_pipe[], t_cmd *cmd,
	pid_t pid);
int		ft_exec_builtin(t_cmd *cmd);
t_bool	ft_is_builtin_command(char *str);


/* Common functions */
void	ft_error(char *message, int exit_status);
void	ft_free_char(char **target);
void    ft_safe_free_split(char ***target);
void	ft_error_display(char *command, char *name, int exit_status);
char	*ft_join_path(const char *prev, const char *next);

/* Token functions */
t_token	*ft_token_create(char *data, t_token_type type);
void	ft_token_add(t_token *new_token, t_token **tokens);
void	ft_token_print(t_token *tokens);
int		ft_token_length(t_token *tokens);
char	**ft_token_array(t_token *tokens, int start, int len);
char	*ft_token_str(t_token *tokens, int start, int len);
void	ft_token_destroy(t_token *token, t_token **tokens);
void	ft_token_free(t_token *tokens);
t_bool	ft_isalnum_str(char *str);
t_bool	ft_check_quot(char *str);

/* Environ functions */
t_env	*ft_env_init(char **environ);
t_env	*ft_env_create(char *str);
void	ft_env_add(t_env *new_env, t_env **envs);
void	ft_env_destroy(char *key);
t_env	*ft_env_get(const char *key, t_env *envs);
void	ft_env_update(const char *key, const char *value);
char    **ft_env_array(t_env *envs);

/* Expansion functions */
void	ft_expand(t_cmd *cmd);

/* Env functions */
int		ft_env();

/* Unset functions */
int		ft_unset(t_cmd *cmd);

/* Export functions */
int		ft_export(t_cmd *cmd);

/* exit function */
int		ft_exit(t_cmd *cmd);

/* cd function */
t_bool	ft_cd(t_cmd *cmd);
t_bool	ft_is_tilde(t_cmd *cmd);
t_bool	ft_isnot_path(t_mshl_data *g_mshl_data, char *pwd);
t_bool	ft_error_cd(char *file);
void	ft_check_dup_str(char **split_path);
void	ft_skip_dot(char **split_path, size_t i, size_t *dot_count, int flag);
char	**ft_skip_and_count_dot(char **split_path, size_t *dot_count,
														size_t *dot_dot_count);
char	*ft_convert_path(char **split_path);

/* pwd function */
t_bool 	ft_pwd();

/* echo function */
int		ft_echo(t_cmd *cmd);

/* parser function */
t_cmd	*ft_parser(t_token *token, t_cmd *cmd);
t_cmd	*ft_cmd_lstnew(void);

/* error function */
t_bool	ft_check_token_error(t_token *tokens);

/* get command path function */
char	*ft_cmd_path_search_binary(const char *cmd);
char	**ft_cmd_path_get_colon(const char *str, const char *default_value);
char	*ft_cmd_path(const char *cmd);

/* pipe functions */
void	ft_pipe_duplicate(t_pipe_state state, int old_pipe[], int new_pipe[]);
void	ft_pipe_update(t_pipe_state state, int old_pipe[], int new_pipe[]);
void	ft_pipe_update_state(t_cmd *command);
void	ft_pipe_destroy(int pipes[]);

/* sigint functions */
void	ft_sigint_handler(int sig);
void	ft_sigint_setter(void (*func)(int));

/* redirect functions */
t_bool	ft_setup_redirect(t_cmd	*cmd);
void	ft_test_print_redirect(t_redirect *redirect);
void	ft_dup_redirect(t_redirect *redirect);
