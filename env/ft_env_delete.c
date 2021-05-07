/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/07 17:44:43 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_delete(char *key, t_env *envs)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = envs;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				envs = current->next;
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
