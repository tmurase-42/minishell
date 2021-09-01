/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/09/01 21:31:45 by tdofuku          ###   ########.fr       */
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
	//mshl_data->pipe[2];
	return (mshl_data);
}

static t_cmd	*run_commandline(char **command)
{
	extern t_mshl_data *g_mshl_data;
	t_cmd		*cmd;
	t_cmd		*current_cmd = NULL;
	t_token		*tokens;

	// printf("command = %s\n", *command);
	tokens = NULL;

	// コマンドが存在すればhistoryに追加する
	if (**command != '\0')
		ft_history_add(*command); // Add new history

	// トークンに分離する
	tokens = ft_lexer(*command);

	// ;とかの「異常なトークン」の検知とエラー吐き出し
	// ここは未実装（村瀬さん）
	// ft_token_print(tokens);
	if (ft_check_token_error(tokens) != TRUE)
		return ;
	// トークンをパースする
	cmd = ft_cmd_lstnew();
	ft_parser(tokens, cmd);
	// ft_token_print(cmd->args);

	// 各コマンドの処理
	current_cmd = cmd;

	// 実行
	ft_exec_commands(current_cmd);

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
