/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 01:30:35 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/28 18:32:20 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			ft_pipe_update(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	printf("pipe_state: %d\n", state);
	if (state == READ_ONLY || state == READ_WRITE)
	{
		printf("OUT: %d\n", OUT);
		printf("IN: %d\n", IN);
		if (close(old_pipe[OUT]) < 0 || close(old_pipe[IN]) < 0)
			ft_error(NULL, "an error occured during closing pipes.", 1);
	}
	if (state == WRITE_ONLY || state == READ_WRITE)
	{
		printf("moving!\n");
		old_pipe[OUT] = new_pipe[OUT];
		old_pipe[IN] = new_pipe[IN];
	}
}
