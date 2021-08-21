/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/07/28 22:29:49 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_mshl_data	*mshl_data_init(t_env *envs)
{
	t_mshl_data	*mshl_data;

	mshl_data = malloc(sizeof(t_mshl_data));
	if (!mshl_data)
		return (NULL);
	mshl_data->argc = 0;
	mshl_data->argv = NULL;
	mshl_data->envs = envs;
	mshl_data->exit_status = 0;
	return (mshl_data);
}

static	void	run_commandline(int ret, char **command, t_env *envs)
{
	t_mshl_data	*mshl_data;
	t_cmd		*cmd;
	t_cmd		*current_cmd;
	t_token		*tokens;

	// printf("command = %s\n", *command);

	tokens = NULL;
	mshl_data = mshl_data_init(envs);

	if (ret == 1)
	{

		// トークンに分離する
		tokens = ft_lexer(*command);
		ft_token_print(tokens);

		ft_check_token_error(tokens);

		// トークンをパースする
		cmd = ft_cmd_lstnew();
		ft_parser(tokens, cmd);

		// コマンドのトークンそれぞれに対して環境変数展開をかける
		// ここは未実装（堂福）

		// もう一度トークンを分離する
		// *command = ft_token_str;
		// tokens = ft_lexer(*command);
		// ft_token_print(tokens);

		// 村瀬さんのテストコード
		// t_cmd	*test;
		// test = ft_cmd_lstnew();
		// test = cmd;
		// int i = 0;
		// while (test)
		// {
		// 	printf("------cmd構造体の値----------\n");
		// 	while (test->args)
		// 	{
		// 		printf("cmd->args->data[%d] = %s\n", i, test->args->data);
		// 		test->args = test->args->next;
		// 	}
		// 	i++;
		// 	test = test->next;
		// 	// コマンド実行
		// 	status = ft_execute_command(test, mshl_data);
		// }
		// free(*command);
		// free(tokens);

		// 関数の実行
		current_cmd = cmd;
		while (current_cmd)
		{
			ft_execute_command(current_cmd, mshl_data);
			current_cmd = current_cmd->next;
		}
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
