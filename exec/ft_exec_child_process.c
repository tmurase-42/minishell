/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:27:55 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/09 17:03:48 by tmurase          ###   ########.fr       */
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
	envs = ft_env_str_array(g_mshl_data->envs);
	path = ft_cmd_path(args[0]);
	if (execve(path, args, envs) == -1)
		ft_error("execve not working.", EXIT_FAILURE);
	ft_safe_free_split(&envs);
}

void	ft_exec_child_process(int new_pipe[], int old_pipe[], t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	int	status;

	ft_sigint_setter(SIG_DFL);
	if (ft_setup_redirect(cmd) == TRUE)
	{
		//格納したredirect構造体の中から、一個ずつfdの情報を取得していく。errorチェックはしない。
		ft_getfd_redirect(cmd);
		//正常にopenできたか、不要なものfileはクローズできるかのエラーチェック
		if (ft_check_redirect(cmd) == FALSE)
			return ;
		//リダイレクトすべきfdだけdupする。
		if (ft_dup_redirect(cmd, 0) == FALSE)
			return ;
	}
	ft_pipe_duplicate(g_mshl_data->pipe_state, old_pipe, new_pipe);
	if (ft_is_builtin_command(cmd->args->data) == TRUE)
	{
		status = ft_exec_builtin(cmd);
		if (cmd->final_greater_fd != 0)
			close(cmd->final_greater_fd);
		if (cmd->final_lesser_fd != 0)
		{
			close(cmd->final_lesser_fd);
			if (ft_delete_tmpfile(cmd, cmd->final_lesser_fd) == FALSE)
				return ;
		}
		exit(status);
	}
	else
		exec_commons(cmd);
}
