/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:41 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/06 19:45:03 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_env	*create_new_env(char *env_str)
{
	t_env	*env;
	char	*sep;

	if (!(env = malloc(sizeof(t_env))))
		ft_error(NULL);
	sep = ft_strchr(env_str, '=');
	if (!sep)
	{
		if (!(env->name = ft_strdup(env_str)))
			ft_error(NULL);
		env->value = NULL;
	}
	else
	{
		if (!(env->name = ft_substr(env_str, 0, sep - env_str)) ||
			!(env->value = ft_strdup(sep + 1)))
			ft_error(NULL);
	}
	env->is_env = TRUE;
	env->next = NULL;
	return (env);
}

t_env		*ft_env_init(char **environ)
{
	size_t	i;
	t_env	*envs;
	t_env	*now_env;

	envs = NULL;
	i = 0;
	while (environ[i])
	{
		now_env = create_new_env(environ[i]);
		ft_env_add(&envs, now_env);
		i++;
	}
	return (envs);
}
