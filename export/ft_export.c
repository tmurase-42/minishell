/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:50:48 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/20 15:14:09 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_cmd *cmd)
{
	if (cmd->args && cmd->args->next)
	{
		return (ft_export_set_envs(cmd));
	}
	else
	{
		return (ft_export_print_envs());
	}
	return (EXIT_SUCCESS);
}
