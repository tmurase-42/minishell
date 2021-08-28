/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/08/28 20:17:14 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//mshl_data->pipe[2];
	return (mshl_data);
}

static void	run_commandline(char **command, t_mshl_data *mshl_data)
{
	t_cmd		*cmd;
	t_cmd		*current_cmd;
	t_token		*tokens;
	char		*token_str;
	int			pipes[2];

	// printf("command = %s\n", *command);
	tokens = NULL;
	token_str = NULL;

	// コマンドが存在すればhistoryに追加する
	if (**command != '\0')
		ft_history_add(*command, mshl_data); // Add new history
	// トークンに分離する
	tokens = ft_lexer(*command);

	// t_token_print(tokens);

	// ;とかの「異常なトークン」の検知とエラー吐き出し
	// ここは未実装（村瀬さん）
	ft_check_token_error(tokens);

	// トークンをパースする
	cmd = ft_cmd_lstnew();
	ft_parser(tokens, cmd);

	// 各コマンドの処理
	current_cmd = cmd;

	// パイプを生成
	if (pipe(pipes) < 0)
		ft_error(NULL, NULL, 1);
	mshl_data->pipe_state = WRITE_ONLY;
	if (current_cmd->next == NULL)
	{
		printf("NO PIPE!\n");
		mshl_data->pipe_state = NO_PIPE;
		if (close(pipes[OUT]) < 0 || close(pipes[IN]) < 0)
			ft_error(NULL, NULL, 1);
	}
	while (current_cmd)
	{
		// トークンに環境変数展開をかける
		ft_expand(current_cmd, mshl_data);

		// トークンを一度文字列に戻す
		token_str = ft_token_str(current_cmd->args, 0, current_cmd->argc);
		ft_token_free(current_cmd->args);

		// 再度トークンに分離する（それをcmd構造体に入れる）
		tokens = ft_lexer(token_str);
		current_cmd->args = tokens;

		// トークン確認用テスト関数
		ft_token_print(current_cmd->args);

		// コマンドを実行する
		ft_execute_command(current_cmd, mshl_data, pipes);
		current_cmd = current_cmd->next;
	}
}

int	main(int argc, char *argv[], char **environ)
{
	char	*command;
	t_env	*envs;
	t_mshl_data	*mshl_data;

	(void)argv;
	(void)argc;
	command = NULL;
	envs = ft_env_init(environ);
	mshl_data = mshl_data_init(envs);
	while (1)
	{
		ft_putstr_fd("\e[36mminishell>\e[0m", 2);
		if (get_next_line(0, &command) < 0)
			return (0);
		run_commandline(&command, mshl_data);
	}
	return (0);
}
