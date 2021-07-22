/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/07/22 09:07:47 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	run_commandline(int ret, char **command, t_env *envs)
{
	t_command	*command_info;
	int			status;
	t_cmd		*cmd;
	t_token		*tokens;

	printf("command = %s\n", *command);
	tokens = NULL;

	command_info = command_init(envs);
	if (ret == 1)
	{
    tokens = ft_lexer(*command);
		ft_token_print(tokens);
		cmd = ft_cmd_lstnew();
		ft_parser(tokens, cmd);
		t_cmd	*test;
		test = ft_cmd_lstnew();
		test = cmd;
		int i = 0;
		while (test)
		{
			printf("------cmd構造体の値----------\n");
			while (test->args)
			{
				printf("cmd->args->data[%d] = %s\n", i, test->args->data);
				test->args = test->args->next;
			}
			i++;
			test = test->next;
		}

		status = execute_command(command_info);
		free(*command);
		free(tokens);
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
