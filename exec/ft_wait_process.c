/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:54:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 22:48:11 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_wait_process(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	int		status;
	t_bool	has_child_process;

	has_child_process = FALSE;

	while(cmd)
	{
		if (cmd->pid > 0)
		{
			if (waitpid(cmd->pid, &status, WUNTRACED) < 0)
				ft_error(NULL, "waitpid failed.", EXIT_FAILURE);
			has_child_process = TRUE;
		}
		cmd = cmd->next;
	}

	if (has_child_process)
	{
		if (WIFEXITED(status))
			g_mshl_data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			else
				ft_putstr_fd("\n", STDERR_FILENO);
			g_mshl_data->exit_status = WTERMSIG(status) + 128;
		}
		else
			ft_error(NULL, "child exited abnormally.", EXIT_FAILURE);
	}
}
