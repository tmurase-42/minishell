/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 01:30:35 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 23:01:06 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	can_write(t_pipe_state state)
{
	if (state == WRITE_ONLY || state == READ_WRITE)
		return (TRUE);
	return (FALSE);
}

void	ft_pipe_create(int new_pipe[])
{
	extern t_mshl_data	*g_mshl_data;

	if (can_write(g_mshl_data->pipe_state) == TRUE)
		return ;
	if (pipe(new_pipe) < 0)
		ft_error(NULL, EXIT_FAILURE);
	g_mshl_data->pipe_state = WRITE_ONLY;
}
