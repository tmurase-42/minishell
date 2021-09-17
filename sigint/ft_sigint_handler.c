/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:31:41 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/17 22:55:13 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sigint_handler(int sig)
{
	extern t_mshl_data	*g_mshl_data;
	int					save_errno;

	save_errno = errno;
	ft_putstr_fd("\b\b  \b\b", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (sig == SIGINT)
	{
		g_mshl_data->exit_status = EXIT_FAILURE;
		g_mshl_data->interrupted = TRUE;
		ft_putstr_fd("\n\e[36mminishell>\e[0m", STDOUT_FILENO);
	}
	errno = save_errno;
}
