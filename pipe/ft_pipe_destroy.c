/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:35:39 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 18:38:02 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe_destroy(int pipes[])
{
	extern t_mshl_data	*g_mshl_data;

	g_mshl_data->pipe_state = NO_PIPE;
	if (close(pipes[OUT]) < 0 || close(pipes[IN]) < 0)
		ft_error("error", "a pipe cannot be closed.", STDERR_FILENO);
}
