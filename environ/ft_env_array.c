/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:31:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 18:36:21 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	get_environ_size(t_env *envs)
{
	size_t	size;

	size = 0;
	while (envs)
	{
		size++;
		envs = envs->next;
	}
	return (size);
}

t_env	**ft_env_array(t_env *envs)
{
	t_env	**environ;
	size_t	env_size;
	size_t	i;

	env_size = get_environ_size(envs);
	if (!(environ = (t_env **)malloc(sizeof(t_env *) * (env_size + 1))))
		ft_error(NULL, EXIT_FAILURE);
	i = 0;
	while (i < env_size)
	{
		environ[i] = envs;
		envs = envs->next;
		i++;
	}
	environ[i] = NULL;
	return (environ);
}
