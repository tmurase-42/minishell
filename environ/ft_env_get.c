/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:38 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/05 18:42:39 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_key_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' ))
	{
		i++;
	}
	return i;
}


t_env	*ft_env_get(const char *key, t_env *envs)
{
	if (!envs || !key)
		return (NULL);
	while (envs)
	{
		if (get_key_len(envs->key) == get_key_len(key)
			&& ft_strncmp(envs->key, key, get_key_len(envs->key)) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}
