/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/07/22 08:02:17 by tmurase          ###   ########.fr       */
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

void	ft_addtoken(t_token *token, char *str)
{
	t_token *next;
	t_token *tmp;

	tmp = ft_calloc(1, sizeof(t_token));
	next = ft_calloc(1, sizeof(t_token));
	tmp = token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	next->prev = tmp;
	next->next = NULL;
	next->data = str;
	tmp->next = next;
}

t_token *test_tokenise(void)
{
	const char *str[] = {"cat", "file1" , "aaaa", "dbbbb", "|", "grep", "test", "|", "wc", "-l", "aaa", "cccc", NULL};
	int i = 0;
	t_token *token;

	while(str[i])
	{
		if (i == 0)
			token = lstnew((char *)str[i]);
		else
		{
			ft_addtoken(token, (char *)str[i]);
		}
		i++;
	}
	return (token);
}


void	run_commandline(int ret, char **command, t_env *envs)
{
	t_command	*command_info;
	int			result;
	int			status;
	t_token		*token;
	t_cmd		*cmd;

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
		token = ft_calloc(1, sizeof(t_token));
		token = test_tokenise();
		cmd = ft_cmd_lstnew();
		ft_parser(token, cmd);
		t_cmd	*test;
		test = ft_cmd_lstnew();
		test = cmd;
		i = 0;
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
		free(token);
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
