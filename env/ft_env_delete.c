/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/06 19:44:05 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_delete(t_env **envs, char *name)
{
	t_env	*now;
	t_env	*prev;

	prev = NULL;
	now = *envs;
	while (now)
	{
		if (ft_strncmp(now->name, name, ft_strlen(name) + 1) == 0)
		{
			if (prev)
				prev->next = now->next;
			else
				*envs = now->next;
			// ft_safe_free_char(&now->name);
			// ft_safe_free_char(&now->value);
			free(now);
			now = NULL;
			break ;
		}
		prev = now;
		now = now->next;
	}
}
