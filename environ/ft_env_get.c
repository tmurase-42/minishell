/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:38 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/07 18:53:13 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*ft_env_get(const char *key, t_env *envs)
{
	if (!envs || !key)
		return (NULL);
	while (envs)
	{
		if (ft_strncmp(envs->key, (char *)key, ft_strlen(envs->key)) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}
