/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mshl_data_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 18:23:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/20 13:42:34 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_mshl_data_destroy(void)
{
	extern t_mshl_data	*g_mshl_data;

	if (g_mshl_data == NULL)
		return ;
	ft_env_destroy_all(g_mshl_data->envs);
	free(g_mshl_data->command);
}
