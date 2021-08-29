/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 12:12:17 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/29 11:06:36 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe_state(t_cmd *cmd, t_mshl_data *mshl_data)
{
	if (cmd->next && cmd->next->next)
		mshl_data->pipe_state = READ_WRITE;
	else if (cmd->next)
		mshl_data->pipe_state = READ_ONLY;
}
