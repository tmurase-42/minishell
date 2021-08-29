/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 08:55:35 by mitchiwak         #+#    #+#             */
/*   Updated: 2021/08/29 14:14:01 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshl_data	*g_mshl_data;

static void wait_process(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	//int		status;
	t_bool	catch_sigint;
	t_bool	has_child_process;
	int		signal;


	catch_sigint = FALSE;
	has_child_process = FALSE;
	while(cmd)
	{
		if (cmd->pid > 0)
		{
			if (waitpid(cmd->pid, &g_mshl_data->exit_status, WUNTRACED) < 0)
				ft_error(NULL, NULL, 1);
			// シグナルの実装で使うかもしれない
			// if (WIFSIGNALED(g_mshl_data->exit_status) && WTERMSIG(g_mshl_data->exit_status) == SIGINT)
			//	catch_sigint = TRUE;
			has_child_process = TRUE;
		}
		cmd = cmd->next;
	}
	if (has_child_process)
	{
		if (WIFEXITED(g_mshl_data->exit_status))
			g_mshl_data->exit_status = WEXITSTATUS(g_mshl_data->exit_status);
		else if (WIFSIGNALED(g_mshl_data->exit_status))
		{
			signal = WTERMSIG(g_mshl_data->exit_status);
			if (signal == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			g_mshl_data->exit_status = signal + 128;
		}
	}
	if (catch_sigint)
		ft_putstr_fd("\n", STDERR_FILENO);
}

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

static void	run_commandline(char **command)
{
	extern t_mshl_data *g_mshl_data;
	t_cmd		*cmd;
	t_cmd		*current_cmd = NULL;
	t_token		*tokens;
	char		*token_str;
	int			pipes[2];

	// printf("command = %s\n", *command);
	tokens = NULL;
	token_str = NULL;

	// コマンドが存在すればhistoryに追加する
	if (**command != '\0')
		ft_history_add(*command); // Add new history
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

	// パイプを生成
	if (pipe(pipes) < 0)
		ft_error(NULL, NULL, 1);
	g_mshl_data->pipe_state = WRITE_ONLY;
	if (current_cmd->next == NULL)
	{
		//printf("NO PIPE!\n");
		g_mshl_data->pipe_state = NO_PIPE;
		if (close(pipes[OUT]) < 0 || close(pipes[IN]) < 0)
			ft_error(NULL, NULL, 1);
	}
	while (current_cmd)
	{
		// トークンに環境変数展開をかける
		ft_expand(current_cmd);

		// トークンを一度文字列に戻す
		token_str = ft_token_str(current_cmd->args, 0, current_cmd->argc);
		ft_token_free(current_cmd->args);

		// 再度トークンに分離する（それをcmd構造体に入れる）
		tokens = ft_lexer(token_str);
		current_cmd->args = tokens;

		// トークン確認用テスト関数
		// ft_token_print(current_cmd->args);

		// コマンドを実行する
		ft_execute_command(current_cmd, pipes);
		current_cmd = current_cmd->next;
	}
	wait_process(cmd);
}

int	main(int argc, char *argv[], char **environ)
{
	char	*command;
	t_env	*envs;
	extern t_mshl_data	*g_mshl_data;

	(void)argv;
	(void)argc;
	command = NULL;
	envs = ft_env_init(environ);
	g_mshl_data = mshl_data_init(envs);
	while (1)
	{
		ft_putstr_fd("\e[36mminishell>\e[0m", 2);
		if (get_next_line(0, &command) < 0)
			return (0);
		run_commandline(&command);
	}
	return (0);
}
