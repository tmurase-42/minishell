/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/05/06 19:59:04 by tdofuku          ###   ########.fr       */
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


#define SPACE 32
#define DOUBLE_QUOT 34
#define SINGLE_QUOT 39
#define NEUTRAL_MODE 100
#define SINGLE_MODE 101
#define DOUBLE_MODE 102

typedef enum		e_bool
{
	FALSE,
	TRUE
}								t_bool;

typedef struct	s_command
{
	struct s_command	*next;
	int					argc;
	char				**argv;
	int					op;
	pid_t				pid;
}								t_command;

typedef struct	s_mode
{
	int	NEUTRAL;
	int	SINGLE;
	int	DOUBLE;
}								t_mode;

typedef struct	s_env
{
	char					*name;
	char					*value;
	t_bool				is_env;
	struct s_env	*next;
}								t_env;

void	run_commandline(int ret, char **command);
int		perse_command(char **command, t_command *command_info);
t_command	*command_init(void);
int	execute_command(t_command *command_info);
int check_meta(char c);


/* Common functions */
int	ft_error(char *str);

/* Env functions */
t_env	*ft_env_init(char **environ);
void	ft_env_add(t_env **envs, t_env *new_env);
void	ft_env_delete(t_env **envs, char *name);
t_env	*ft_env_get(const char *name, t_env *envs);
