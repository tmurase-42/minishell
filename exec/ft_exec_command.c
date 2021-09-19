/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 03:24:41 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/19 12:39:04 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	process_redirect(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	int					result;

	g_mshl_data->interrupted = FALSE;
	result = ft_getfd_redirect(cmd);
	result = ft_check_redirect(cmd);
	if (result == FALSE)
	{
		ft_error_display(cmd->redirect->open_filepath, "system call error", 1);
		return (FALSE);
	}
	if (g_mshl_data->interrupted == TRUE)
	{
		g_mshl_data->interrupted = FALSE;
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	process_redirect_for_builtin(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	int					result;

	result = TRUE;
	if (ft_setup_redirect(cmd) == TRUE)
	{
		result = ft_getfd_redirect(cmd);
		result = ft_check_redirect(cmd);
		result = ft_dup_redirect(cmd, 1);
		if (result == FALSE)
		{
			ft_error_display("minishell", "system call error", 1);
			return (FALSE);
		}
	}
	g_mshl_data->exit_status = ft_exec_builtin(cmd);
	ft_backup_fd(cmd);
	return (TRUE);
}

static t_bool	fork_process(t_cmd *cmd, int old_pipe[])
{
	pid_t				pid;
	int					new_pipe[2];

	if (pipe(new_pipe) < 0)
	{
		ft_pipe_destroy(old_pipe);
		ft_error(NULL, "cannot create a pipe.", EXIT_FAILURE);
	}
	if (ft_setup_redirect(cmd) == TRUE)
		if (process_redirect(cmd) == FALSE)
			return (FALSE);
	pid = fork();
	if (pid < 0)
	{
		ft_pipe_destroy(old_pipe);
		ft_pipe_destroy(new_pipe);
	}
	if (pid == 0)
		ft_exec_child_process(new_pipe, old_pipe, cmd);
	else
		ft_exec_parent_process(new_pipe, old_pipe, cmd, pid);
	return (TRUE);
}

t_bool	ft_exec_command(t_cmd *cmd, int old_pipe[])
{
	extern t_mshl_data	*g_mshl_data;

	if (cmd->argc == 0 || !cmd->args || cmd->args->data == NULL)
	{
		g_mshl_data->exit_status = EXIT_FAILURE;
		return (FALSE);
	}
	if (g_mshl_data->pipe_state == NO_PIPE
		&& ft_is_builtin_command(cmd->args->data))
	{
		return (process_redirect_for_builtin(cmd));
	}
	if (fork_process(cmd, old_pipe) == FALSE)
		return (FALSE);
	return (TRUE);
}
