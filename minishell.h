/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/17 17:23:05 by tdofuku          ###   ########.fr       */
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

#define DOUBLE_QUOT 34
#define SINGLE_QUOT 39
#define NEUTRAL_MODE 100
#define SINGLE_MODE 101
#define DOUBLE_MODE 102
#define BUFF_SIZE 4096

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
	char	**value;
}					t_node;

typedef enum	e_tokentype{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_TAB = '\t',
	CHAR_NULL = 0, // 深掘りすぎ。不要
	D_SEMICOLON = -4, // 深掘りすぎ。不要
	DOUBLE_GREATER = -3, // >> ってこと。
	IO_NUMBER = -2, //謎
	TOKEN = -1, //謎
}				t_token_type;

typedef enum	e_token_state{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_GENERAL,
}				t_token_state;

typedef struct s_token	t_token;

struct			s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*data;
};

typedef struct	s_env
{
	char					*key;
	char					*value;
	t_bool				is_env;
	struct s_env	*next;
}				t_env;

typedef struct	s_command
{
	struct s_command	*next;
	int					argc;
	char				**argv;
	int					op;
	pid_t				pid;
	t_env				*envs;
	int					exit_status;
}				t_command;

void	run_commandline(int ret, char **command, t_env *envs);
t_token	*ft_lexer(char *str);
t_command	*command_init(t_env *envs);
int	execute_command(t_command *command_info);

/* Common functions */
void	ft_error(char *message, char *command);
void	ft_free_char(char **target);
void	ft_error_identifier(char *command, char *name);

/* Token functions */
t_token	*ft_token_create(char *data, t_token_type type);
void	ft_token_add(t_token *new_token, t_token **tokens);
void	ft_token_print(t_token *tokens);

/* Environ functions */
t_env	*ft_env_init(char **environ);
t_env	*ft_env_create(char *str);
void	ft_env_add(t_env *new_env, t_env **envs);
void	ft_env_delete(char *key, t_env *envs);
t_env	*ft_env_get(const char *key, t_env *envs);
void	ft_env_update(const char *key, const char *value, t_env *envs);

/* Expansion functions */
char	*ft_expand(char *str, t_command *command_info);

/* Env functions */
int		ft_env(t_command *command_info);


/* Unset functions */
int		ft_unset(t_command *command_info);

/* Export functions */
int		ft_export(t_command *command_info);

/* exit function */
t_bool	ft_exit(t_command *command_info);


/* cd function */
t_bool ft_cd(t_command *command_info);

/* pwd function */
t_bool ft_pwd(t_command *command_info);
