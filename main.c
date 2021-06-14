/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/06/15 08:12:23 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *lstnew(char *str)
{
	t_token	*tmp;

	tmp = ft_calloc(1, sizeof(t_token));
	tmp->prev = NULL;
	tmp->next = NULL;
	tmp->data = str;

	return (tmp);
}

t_token *test_tokenise(void)
{
	const char *str[] = {"cat", "file1", "|", "grep", "a", "|", "wc", "-l", NULL};
	int i = 0;
	t_token *new;

	while(str[i])
	{
		if (i == 0)
			new = lstnew((char *)str[i]);
		printf("new = %s\n", new->data);
		i++;
	}
	return (new);
}

void	run_commandline(int ret, char **command, t_env *envs)
{
	t_command	*command_info;
	int			result;
	int			status;
	t_token		*test;

	command_info = command_init(envs);
	if (ret == 1)
	{
		result = ft_lexer(command, command_info);
		int i = 0;
		printf("commnad_info->argc = %d\n", command_info->argc);
		while (i < command_info->argc)
		{
			printf("commnad_info->argv[%d] = %s\n", i, command_info->argv[i]);
			i++;
		}

		test = ft_calloc(1, sizeof(t_token));
		test = test_tokenise();
		status = execute_command(command_info);
		free(*command);
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
