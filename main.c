/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitchiwaki <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/04/11 18:05:15 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commandline(int ret, char **command)
{
	t_command	*command_info;
	int			result;

	command_info = command_init();
	if (ret == 1)
	{
		result = perse_command(command, command_info);
			
		free(*command);
		*command = NULL;
	}
}

int	main(int argc, char *argv[])
{
	char	*command;
	int		ret;
	int		prompt;

	(void)argv;
	(void)argc;
	prompt = 1;
	command = NULL;
	while (1)
	{
		if (prompt)
		{
			ft_putstr_fd("minishell>", 2);
			prompt = 0;
		}
		if ((ret = get_next_line(0, &command)) < 0)
			return (0);
		run_commandline(ret, &command);
		prompt = ret == 1 ? 1 : 0;
	}
	return (0);
}
