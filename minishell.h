/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/28 14:09:36 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SPACE 32
#define TURE 1
#define FALSE 0
#define DOUBLE_QUO 34
#define SINGLE_QUO 39

typedef struct			s_command
{
	struct s_command	*next;
	int					argc;
	char				**argv;
	int					op;
	pid_t				pid;
}						t_command;



void	run_commandline(int ret, char **command);
int		perse_command(char **command, t_command *command_info);
t_command	*command_init(void);
int	execute_command(t_command *command_info);
int check_meta(char c);




