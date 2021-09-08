/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_str_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 20:26:21 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 19:06:13 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	can_generate_environ(t_env *env)
{
	if (env->value == NULL)
		return (FALSE);
	if (env->is_env == FALSE)
		return (FALSE);
	return (TRUE);
}

static size_t	get_environ_size(t_env *envs)
{
	size_t	size;

	size = 0;
	while (envs)
	{
		if (can_generate_environ(envs))
			size++;
		envs = envs->next;
	}
	return (size);
}

char	**ft_env_str_array(t_env *envs)
{
	char	**environ;
	char	*tmp;
	size_t	env_size;
	size_t	i;

	env_size = get_environ_size(envs);
	if (!(environ = (char **)malloc(sizeof(char *) * (env_size + 1))))
		ft_error(NULL, EXIT_FAILURE);
	i = 0;
	while (i < env_size)
	{
		if (can_generate_environ(envs))
		{
			if (!(environ[i] = ft_strjoin(envs->key, "=")))
				ft_error(NULL, EXIT_FAILURE);
			tmp = environ[i];
			if (!(environ[i] = ft_strjoin(environ[i], envs->value)))
				ft_error(NULL, EXIT_FAILURE);
			free(tmp);
			i++;
		}
		envs = envs->next;
	}
	environ[i] = NULL;
	return (environ);
}
