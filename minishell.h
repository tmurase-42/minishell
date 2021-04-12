/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:52:14 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/11 07:55:37 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>



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
