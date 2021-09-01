/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/01 17:44:02 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <string.h>

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
	DOUBLE_GREATER = -4, // >> ってこと。
	DOUBLE_LESSER = -3, // << ってこと。
	IO_NUMBER = -2, //謎
	TOKEN = -1, //謎
}				t_token_type;

typedef struct s_token	t_token;

struct			s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*data;
};

typedef struct s_cmd t_cmd;
struct			s_cmd
{
	t_token	*args;
	int		argc;
	struct	s_cmd *next;
	pid_t	pid;
	// int		op;
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
}				t_mshl_data;

t_token	*ft_lexer(char *str);
void	ft_execute_command(t_cmd *cmd, int pipes[]);

/* Common functions */
void	ft_error(char *message, char *command, int status_num);
void	ft_free_char(char **target);
void    ft_safe_free_split(char ***target);
void	ft_error_display(char *command, char *name, int exit_status);

/* Token functions */
t_token	*ft_token_create(char *data, t_token_type type);
void	ft_token_add(t_token *new_token, t_token **tokens);
void	ft_token_print(t_token *tokens);
int		ft_token_length(t_token *tokens);
char	**ft_token_array(t_token *tokens, int start, int len);
char	*ft_token_str(t_token *tokens, int start, int len);
void	ft_token_destroy(t_token *token, t_token **tokens);
void	ft_token_free(t_token *tokens);

/* Environ functions */
t_env	*ft_env_init(char **environ);
t_env	*ft_env_create(char *str);
void	ft_env_add(t_env *new_env, t_env **envs);
void	ft_env_delete(char *key, t_env *envs);
t_env	*ft_env_get(const char *key, t_env *envs);
void	ft_env_update(const char *key, const char *value, t_env *envs);
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
t_bool		ft_cd(t_cmd *cmd);

/* pwd function */
t_bool 	ft_pwd();

/* echo function */
int		ft_echo(t_cmd *cmd);

/* parser function */
t_cmd	*ft_parser(t_token *token, t_cmd *cmd);
t_cmd	*ft_cmd_lstnew(void);

/* error function */
t_bool	ft_check_token_error(t_token *tokens);

/* history functions */
int		ft_history_add(char *line);
int		ft_history();

/* get command path function */
char	*ft_cmd_path(const char *cmd);

/* pipe functions */
void	ft_pipe_duplicate(t_pipe_state state, int old_pipe[], int new_pipe[]);
void	ft_pipe_update(t_pipe_state state, int old_pipe[], int new_pipe[]);
void	ft_pipe_create(t_pipe_state state, int new_pipe[]);
void	ft_pipe_state(t_cmd *command);
