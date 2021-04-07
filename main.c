/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitchiwaki <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/04/07 21:24:12 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

void	run_commandline(int ret, char **command)
{
	if (ret == 1)
	{
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
		//run_commandline(ret, &command);
		prompt = ret == 1 ? 1 : 0;
	}
	return (0);
}
