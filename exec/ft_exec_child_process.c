/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:27:55 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 19:35:39 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		exec_commons(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char	**args;
	char	**envs;
	char	*path;

	args = ft_token_array(cmd->args, 0, cmd->argc);
	envs = ft_env_array(g_mshl_data->envs);
	path = ft_cmd_path(args[0]);
	// printf("\ncmd->argc: %d\n", cmd->argc);
	// printf("args: %s\n", *args);
	// printf("cmd->args->data: %s\n", cmd->args->data);
	if (execve(path, args, envs) == -1)
		ft_error("do not work exec", cmd->args->data, EXIT_FAILURE);
	ft_safe_free_split(&envs);
}

void	ft_exec_child_process(int new_pipe[], int old_pipe[], t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	// 子プロセスの場合は、親→子への書き込みはありえないのでcloseする
	// close(new_pipe[OUT]);
	// 子プロセスの場合は、子→親の読み込みはありえないのでcloseする
	// close(old_pipe[IN]);
	//	NO_PIPE,
	//	READ_ONLY,
	//	WRITE_ONLY,
	//	READ_WRITE
	ft_sigint_setter(SIG_DFL);

	if (g_mshl_data->pipe_state == READ_ONLY || g_mshl_data->pipe_state == READ_WRITE)
	{
		// 割り当てたファイルディスクリプタは閉じる
		close(old_pipe[IN]);
		// 標準入力として割り当て
		dup2(old_pipe[OUT], STDIN_FILENO);
		// 閉じる
		close(old_pipe[OUT]);
	}
	if (g_mshl_data->pipe_state == WRITE_ONLY || g_mshl_data->pipe_state == READ_WRITE)
	{
		close(new_pipe[OUT]);
		// 標準出力に割り当て
		dup2(new_pipe[IN], STDOUT_FILENO);
		// 割り当てたファイルディスクリプタは閉じる
		close(new_pipe[IN]);
	}

	// printf("fefe\n");
	// ft_pipe_duplicate(g_mshl_data->pipe_state, g_mshl_data->pipe, new_pipe);
	// printf("new_pipe: %d\n", *new_pipe);

	if (is_builin_command(cmd->args->data) == TRUE)
		exit(ft_exec_builtin(cmd));
	else
		exec_commons(cmd);
}
