/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_duplicate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 01:30:35 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 17:37:33 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	can_write(t_pipe_state state)
{
	if (state == WRITE_ONLY || state == READ_WRITE)
		return (TRUE);
	return (FALSE);
}

static t_bool	can_read(t_pipe_state state)
{
	if (state == READ_ONLY || state == READ_WRITE)
		return (TRUE);
	return (FALSE);
}

void	ft_pipe_duplicate(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (can_read(state) == TRUE)
	{
		if (close(old_pipe[IN]) < 0
			|| dup2(old_pipe[OUT], STDIN_FILENO) < 0
			|| close(old_pipe[OUT]) < 0)
		{
			ft_error("error", "a pipe cannot be set up.", 1);
		}
	}
	if (can_write(state) == TRUE)
	{
		if (close(new_pipe[OUT]) < 0
			|| dup2(new_pipe[IN], STDOUT_FILENO) < 0
			|| close(new_pipe[IN]) < 0)
		{
			ft_error("error", "a pipe cannot be set up.", 1);
		}
	}
}
