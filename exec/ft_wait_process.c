/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:54:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 23:01:06 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_wait_process(t_cmd *cmd)
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
				ft_error(NULL, EXIT_FAILURE);
			// シグナルの実装で使うかもしれない
			if (WIFSIGNALED(g_mshl_data->exit_status) && WTERMSIG(g_mshl_data->exit_status) == SIGINT)
				catch_sigint = TRUE;
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
		if (catch_sigint)
			ft_putstr_fd("\n", STDERR_FILENO);
	}
}
