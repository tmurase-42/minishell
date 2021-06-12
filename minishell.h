/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/12 14:48:10 by mitchiwak        ###   ########.fr       */
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


#define SPACE 32
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

typedef enum		e_Node_kind
{
	ND_PIPE;
	ND_COMMAND;
}					t_Node_kind;

typedef struct		e_Node
{
	t_Node_kind kind;
	t_Node  *lefthand_side;
	t_Node	*righthand_side;
	char	**value;
}					t_Node;

typedef enum		e_token_state{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_GENERAL,
}								t_token_state;

typedef struct	s_env
{
	char					*key;
	char					*value;
	t_bool				is_env;
	struct s_env	*next;
}								t_env;

typedef struct	s_command
{
	struct s_command	*next;
	int					argc;
	char				**argv;
	int					op;
	pid_t				pid;
	t_env				*envs;
	int					exit_status;
}								t_command;

typedef struct	s_mode
{
	int	NEUTRAL;
	int	SINGLE;
	int	DOUBLE;
}								t_mode;

void	run_commandline(int ret, char **command, t_env *envs);
int		ft_lexer(char **command, t_command *command_info);
t_command	*command_init(t_env *envs);
int	execute_command(t_command *command_info);
int check_meta(char c);


/* Common functions */
void	ft_error(char *message, char *command);
void	ft_free_char(char **target);
void	ft_error_identifier(char *command, char *name);

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
