/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 12:12:17 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/29 12:43:12 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe_state(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;

	if (cmd->next && cmd->next->next)
		g_mshl_data->pipe_state = READ_WRITE;
	else if (cmd->next)
		g_mshl_data->pipe_state = READ_ONLY;
}
