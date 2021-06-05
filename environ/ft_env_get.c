/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:38 by tdofuku           #+#    #+#             */
/*   Updated: 2021/06/05 14:20:25 by tdofuku          ###   ########.fr       */
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
		if (ft_strncmp(envs->key, key, get_key_len(key)) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}
