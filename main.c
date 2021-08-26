/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/08/26 22:50:21 by tdofuku          ###   ########.fr       */
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
	return (mshl_data);
}

static int	run_commandline(int ret, char **command, t_mshl_data *mshl_data)
{
	t_cmd		*cmd;
	t_cmd		*current_cmd;
	t_token		*tokens;
	char		*token_str;
	// char		*tmp_str;

	// printf("command = %s\n", *command);
	tokens = NULL;
	token_str = NULL;

	// コマンドが存在すればhistoryに追加する
	if (**command != '\0')
		ft_history_add(*command, mshl_data); // Add new history
	if (ret == 1)
	{
		// トークンに分離する
		tokens = ft_lexer(*command);

		// ;とかの「異常なトークン」の検知とエラー吐き出し
		// ここは未実装（村瀬さん）
		ft_check_token_error(tokens);

		// トークンをパースする
		cmd = ft_cmd_lstnew();
		ft_parser(tokens, cmd);

		// 各コマンドの処理
		current_cmd = cmd;
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
			// ft_token_print(current_cmd->args);

			// コマンドを実行する
			ret = ft_execute_command(current_cmd, mshl_data);
			current_cmd = current_cmd->next;
		}
	}
	return ret;
}

int	main(int argc, char *argv[], char **environ)
{
	char	*command;
	int		ret;
	int		prompt;
	t_env	*envs;
	t_mshl_data	*mshl_data;

	(void)argv;
	(void)argc;
	prompt = 1;
	command = NULL;
	envs = ft_env_init(environ);
	mshl_data = mshl_data_init(envs);

	while (1)
	{
		if (prompt)
		{
			ft_putstr_fd("minishell>", 2);
			prompt = 0;
		}
		if ((ret = get_next_line(0, &command)) < 0)
			return (0);
		ret = run_commandline(ret, &command, mshl_data);
		prompt = ret == 1 ? 1 : 0;
		if (ret == 1)
			prompt = ret;
		else
			prompt = 0;
	}
	return (0);
}
