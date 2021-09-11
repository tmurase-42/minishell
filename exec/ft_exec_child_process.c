/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:27:55 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/11 01:29:14 by tdofuku          ###   ########.fr       */
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
	errno = 0;
	if (execve(path, args, envs) == -1)
	{
		if (errno == ENOENT)
			ft_error(path, NULL, STATUS_CMD_NOT_FOUND);
		else
			ft_error(path, NULL, STATUS_CMD_NOT_EXECUTABLE);
	}
	ft_safe_free_split(&envs);
}

void	ft_exec_child_process(int new_pipe[], int old_pipe[], t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	int	status;

	ft_sigint_setter(SIG_DFL);
	ft_pipe_duplicate(g_mshl_data->pipe_state, old_pipe, new_pipe);
	if (ft_dup_redirect(cmd, 0) == FALSE)
		ft_error(NULL, "minishell", 1);
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
