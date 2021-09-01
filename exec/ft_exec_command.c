/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/08/28 20:32:58 by tdofuku          ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void			ft_exec_command(t_cmd *cmd, int old_pipe[])
{
	extern t_mshl_data	*g_mshl_data;
	pid_t	pid;
	int		new_pipe[2];

	// コマンドの中身がなかった場合の例外処理
	if (cmd->argc == 0 || !cmd->args || cmd->args->data == NULL)
	{
		g_mshl_data->exit_status = EXIT_FAILURE;
		return ;
	}
	// パイプがない → 場合
	if (g_mshl_data->pipe_state == NO_PIPE && is_builin_command(cmd->args->data))
	{
		g_mshl_data->exit_status = ft_exec_builtin(cmd);
		return ;
	}
	// 新しいパイプを生成
	if (pipe(new_pipe) < 0) {
		// パイプ生成失敗
		// 上で開いたパイプを閉じてから終了
		close(old_pipe[IN]);
		close(old_pipe[OUT]);
		ft_error("popen2", NULL, 1);
	}
	// プロセスの生成
	pid = fork();
	if (pid < 0)
	{
		// 上で開いたパイプを閉じる
		if (close(old_pipe[IN]) < 0 || close(old_pipe[OUT] < 0)
			|| close(new_pipe[IN]) < 0 || close(new_pipe[OUT]) < 0)
		{
			ft_error("resources runnout.", cmd->args->data, 0);
		}
	}
	if (pid == 0) // 子プロセスの処理
	{
		ft_exec_child_process(new_pipe, old_pipe, cmd);
	}
	ft_sigint_setter(SIG_IGN);
	ft_pipe_update(g_mshl_data->pipe_state, old_pipe, new_pipe);
	cmd->pid = pid;
	// パイプステータスの更新
	ft_pipe_update_state(cmd);
}


void	ft_exec_commands(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char		*token_str;
	t_token		*tokens;
	int			pipes[2];

	tokens = NULL;
	token_str = NULL;

	// パイプを生成
	ft_pipe_create(pipes);

	// コマンドが一つだったらNO_PIPEステータスにする
	if (cmd->next == NULL)
		g_mshl_data->pipe_state = NO_PIPE;

	// 実行
	while (cmd)
	{
		// トークンに環境変数展開をかける
		ft_expand(cmd);

		// トークンを一度文字列に戻す
		token_str = ft_token_str(cmd->args, 0, cmd->argc);
		ft_token_free(cmd->args);

		// 再度トークンに分離する（それをcmd構造体に入れる）
		tokens = ft_lexer(token_str);
		cmd->args = tokens;
		// ft_token_print(tokens);

		// トークン確認用テスト関数
		// ft_token_print(cmd->args);

		// コマンドを実行する
		ft_exec_command(cmd, pipes);
		cmd = cmd->next;
	}
}
