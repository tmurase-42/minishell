/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/06/12 14:24:06 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commandline(int ret, char **command, t_env *envs)
{
	t_command	*command_info;
	int			result;
	int			status;

	command_info = command_init(envs);
	if (ret == 1)
	{
		result = perse_command(command, command_info);
		int i = 0;
		printf("commnad_info->argc = %d\n", command_info->argc);
		while (i < command_info->argc)
		{
			printf("commnad_info->argv[%d] = %s\n", i, command_info->argv[i]);
			i++;
		}
		status = execute_command(command_info);
		free(*command);
		*command = NULL;
	}
}

int	main(int argc, char *argv[], char **environ)
{
	char	*command;
	int		ret;
	int		prompt;
	t_env	*envs;

	(void)argv;
	(void)argc;
	prompt = 1;
	command = NULL;
	envs = ft_env_init(environ);

	while (1)
	{
		if (prompt)
		{
			ft_putstr_fd("minishell>", 2);
			prompt = 0;
		}
		if ((ret = get_next_line(0, &command)) < 0)
			return (0);
		run_commandline(ret, &command, envs);
		prompt = ret == 1 ? 1 : 0;
		if (ret == 1)
			prompt = ret;
		else
			prompt = 0;
	}
	return (0);
}
