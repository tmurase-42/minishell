/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 01:30:35 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/29 11:05:46 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	can_write(t_pipe_state state)
{
	if (state == WRITE_ONLY || state == READ_WRITE)
	{
		return (TRUE);
	}
	return (FALSE);
}

void			ft_pipe_create(t_pipe_state state, int new_pipe[])
{
	if (can_write(state) == TRUE)
	{
		if (pipe(new_pipe) < 0)
		{
			ft_error(NULL, NULL, 1);
		}
	}
}
