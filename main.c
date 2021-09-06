/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/09/06 10:53:16 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshl_data	*g_mshl_data;

static t_mshl_data	*mshl_data_init(t_env *envs)
{
	t_mshl_data	*mshl_data;

	mshl_data = malloc(sizeof(t_mshl_data));
	if (!mshl_data)
		return (NULL);
	mshl_data->argc = 0;
	mshl_data->argv = NULL;
	mshl_data->envs = envs;
	mshl_data->exit_status = 0;
	mshl_data->histories = NULL;
	mshl_data->pipe_state = WRITE_ONLY;
	mshl_data->interrupted = FALSE;
	return (mshl_data);
}

static t_cmd	*run_commandline(char **command)
{
	extern t_mshl_data *g_mshl_data;
	t_cmd		*cmd;
	t_token		*tokens;

	tokens = NULL;

	// 文字列をトークンに分離する
	tokens = ft_lexer(*command);

	// 異常なトークンの検知とエラー吐き出し
	//if (ft_check_token_error(tokens) != TRUE)
		//return NULL;

	// トークンをパースする
	cmd = ft_cmd_lstnew();
	ft_parser(tokens, cmd);

	// テストプリント
	//ft_token_print(cmd->args);

	// 実行
	ft_exec_commands(cmd);

	// 返却
	return cmd;
}

int	main(int argc, char *argv[], char **environ)
{
	char	*command;
	t_env	*envs;
	extern t_mshl_data	*g_mshl_data;
	t_cmd	*cmd;

	(void)argv;
	(void)argc;
	command = NULL;
	envs = ft_env_init(environ);
	g_mshl_data = mshl_data_init(envs);

	if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
	{
		run_commandline(&argv[2]);
		return g_mshl_data->exit_status;
	}
	while (1)
	{
		//g_mshl_data->interrupted = FALSE;
		//g_mshl_data->exit_status = 0;
		ft_sigint_setter(ft_sigint_handler);

		command = readline("\e[36mminishell>\e[0m");
		if (command == NULL)
			exit(EXIT_FAILURE);
		else if (ft_strlen(command) > 0)
		{
			add_history(command);
			cmd = run_commandline(&command);
			ft_wait_process(cmd);
		}
	}
	return (0);
}
