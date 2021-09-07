/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/07 15:36:18 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_destroy(char *key)
{
	extern t_mshl_data	*g_mshl_data;
	t_env				*current;
	t_env				*prev;

	prev = NULL;
	current = g_mshl_data->envs;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				g_mshl_data->envs = current->next;
			ft_free_char(&current->key);
			ft_free_char(&current->value);
			free(current);
			current = NULL;
			break ;
		}
		prev = current;
		current = current->next;
	}
}
