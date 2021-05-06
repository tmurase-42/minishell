/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:38 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/06 19:58:18 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*ft_env_get(const char *name, t_env *envs)
{
	t_env			*now;

	if (!envs || !name)
		return (NULL);
	now = envs;
	while (now)
	{
		if (ft_strncmp(now->name, (char *)name, ft_strlen(now->name)) == 0)
			return (now);
		now = now->next;
	}
	return (NULL);
}
