/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:23:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/05 19:04:24 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fork_process(t_cmd *cmd, int old_pipe[])
{
	extern t_mshl_data	*g_mshl_data;
	pid_t	pid;
	int		new_pipe[2];

	// 新しいパイプを生成
	if (pipe(new_pipe) < 0) {
		ft_pipe_destroy(old_pipe); // 失敗した場合は、上で開いたパイプを閉じてから終了
		ft_error("cannot create a pipe.", EXIT_FAILURE);
	}

	// プロセスの生成
	pid = fork();
	if (pid < 0)
	{
		ft_pipe_destroy(old_pipe); // 失敗した場合は、上で開いたパイプを閉じてから終了
		ft_pipe_destroy(new_pipe); // 失敗した場合は、上で開いたパイプを閉じてから終了
	}
	if (pid == 0) // 子プロセスの処理
		ft_exec_child_process(new_pipe, old_pipe, cmd);
	else // 親プロセスの処理
		ft_exec_parent_process(new_pipe, old_pipe, cmd, pid);
}

static void	exec_command(t_cmd *cmd, int old_pipe[])
{
	extern t_mshl_data	*g_mshl_data;

	// コマンドの中身がなかった場合の例外処理
	if (cmd->argc == 0 || !cmd->args || cmd->args->data == NULL)
	{
		g_mshl_data->exit_status = EXIT_FAILURE;
		return ;
	}
	// パイプがない → 場合
	if (g_mshl_data->pipe_state == NO_PIPE && ft_is_builtin_command(cmd->args->data))
	{
		//パイプがない場合、リダイレクトの準備をここでする？
		ft_setup_redirect(cmd);
		g_mshl_data->exit_status = ft_exec_builtin(cmd);
		return ;
	}
	fork_process(cmd, old_pipe);
}

void	ft_exec_commands(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char		*token_str;
	t_token		*tokens;
	int			old_pipe[2];

	tokens = NULL;
	token_str = NULL;

	// 古いパイプを生成
	if (pipe(old_pipe) < 0)
		ft_error("cannot create a pipe.", EXIT_FAILURE);
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
		// 再度トークンに分離する（それをcmd構造体に入れる）
		tokens = ft_lexer(token_str);
		// 再生成したトークンを代入する
		ft_token_free(cmd->args);
		cmd->args = tokens;
		// コマンドを実行する
		exec_command(cmd, old_pipe);
		// 次のコマンドへ
		cmd = cmd->next;
	}
}
