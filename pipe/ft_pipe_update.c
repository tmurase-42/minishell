/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 01:30:35 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 23:04:14 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe_update(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (state == READ_ONLY || state == READ_WRITE)
	{
		if (close(old_pipe[OUT]) < 0 || close(old_pipe[IN]) < 0)
			ft_error("a pipe cannot be closed.", EXIT_FAILURE);
	}
	if (state == WRITE_ONLY || state == READ_WRITE)
	{
		old_pipe[OUT] = new_pipe[OUT];
		old_pipe[IN] = new_pipe[IN];
	}
}
