/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:50:48 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 01:35:51 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_cmd *cmd)
{
	if (cmd->argc == 1)
	{
		return (ft_export_print_envs());
	}
	else
	{
		return (ft_export_set_envs(cmd));
	}
	return (EXIT_SUCCESS);
}
