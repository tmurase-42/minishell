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


static t_bool	is_builin_command(char *str)
{
	const char *commands[] = {"exit", "cd", "env", "unset", "export", "echo", "pwd", "history", NULL};
	int		i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (commands[i])
	{
		if (ft_strncmp(str, commands[i], ft_strlen(commands[i])) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static int	exec_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args->data, "echo",ft_strlen("echo")) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->args->data, "exit", ft_strlen("exit")) == 0)
		return (ft_exit(cmd));
	if (ft_strncmp(cmd->args->data, "env", ft_strlen("env")) == 0)
		return (ft_env());
	if (ft_strncmp(cmd->args->data, "export", ft_strlen("export")) == 0)
		return (ft_export(cmd));
	if (ft_strncmp(cmd->args->data, "unset", ft_strlen("unset")) == 0)
		return (ft_unset(cmd));
	if (ft_strncmp(cmd->args->data, "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd->args->data, "cd", ft_strlen("cd")) == 0)
		return (ft_cd(cmd));
	if (ft_strncmp(cmd->args->data, "history", ft_strlen("history")) == 0)
		return (ft_history());
	return (EXIT_FAILURE);
}

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

static void		exec_command(t_cmd *cmd, int old_pipe[])
{
	extern t_mshl_data	*g_mshl_data;
	pid_t	pid;
	//pid_t	wpid;
	//int		status;
	int		new_pipe[2];

	// パイプじゃない場合
	if (g_mshl_data->pipe_state == NO_PIPE && is_builin_command(cmd->args->data))
	{
		g_mshl_data->exit_status = exec_builtin(cmd);
		return ;
	}

	// パイプの場合
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
		close(old_pipe[IN]);
		close(old_pipe[OUT]);
		close(new_pipe[IN]);
		close(new_pipe[OUT]);
		ft_error("resources runnout.", cmd->args->data, 0);
	}
	if (pid == 0) // 子プロセスの処理
	{
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
			exit(exec_builtin(cmd));
		else
			exec_commons(cmd);
	}
	ft_sigint_setter(SIG_IGN);
	// else // 親プロセスの処理
	//{
	//	if (pid > 0)
	//		wpid = waitpid(pid, &status, WUNTRACED);
	//}
	// printf("ft_pipe_update: start: %s\n", cmd->args->data);
	ft_pipe_update(g_mshl_data->pipe_state, old_pipe, new_pipe);
	cmd->pid = pid;
}

void			ft_execute_command(t_cmd *cmd, int pipes[])
{
	extern t_mshl_data	*g_mshl_data;

	// コマンドの中身がなかった場合の例外処理
	if (cmd->argc == 0 || !cmd->args || cmd->args->data == NULL)
	{
		g_mshl_data->exit_status = EXIT_FAILURE;
		return ;
	}
	// printf("g_mshl_data->pipe_state: %d\n", g_mshl_data->pipe_state);
	// 実行
	exec_command(cmd, pipes);
	// パイプステータスの更新
	ft_pipe_update_state(cmd);
}
