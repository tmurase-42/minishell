/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_duplicate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 01:30:35 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/27 01:34:19 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	can_write(t_pipe_state state)
{
	if (state == PIPE_WRITE_ONLY || state == PIPE_READ_WRITE)
	{
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	can_read(t_pipe_state state)
{
	if (state == PIPE_READ_ONLY || state == PIPE_READ_WRITE)
	{
		return (TRUE);
	}
	return (FALSE);
}

void			ft_pipe_duplicate(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (can_read(state) == TRUE)
	{
		if (close(old_pipe[PIPE_IN]) < 0 ||
			dup2(old_pipe[PIPE_OUT], STDIN_FILENO) < 0 ||
			close(old_pipe[PIPE_OUT]) < 0)
		{
			ft_error(NULL, NULL, 1);
		}
	}
	if (can_write(state) == TRUE)
	{
		if (close(new_pipe[PIPE_OUT]) < 0 ||
			dup2(new_pipe[PIPE_IN], STDOUT_FILENO) < 0 ||
			close(new_pipe[PIPE_IN]) < 0)
		{
			ft_error(NULL, NULL, 1);
		}
	}
}

