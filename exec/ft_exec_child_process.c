/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:27:55 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/04 11:13:05 by tdofuku          ###   ########.fr       */
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
	if (execve(path, args, envs) == -1)
		ft_error("execve not working.", EXIT_FAILURE);
	ft_safe_free_split(&envs);
}

void	ft_exec_child_process(int new_pipe[], int old_pipe[], t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;

	ft_sigint_setter(SIG_DFL);
	ft_pipe_duplicate(g_mshl_data->pipe_state, old_pipe, new_pipe);
	if (ft_is_builtin_command(cmd->args->data) == TRUE)
		exit(ft_exec_builtin(cmd));
	else
		exec_commons(cmd);
}
