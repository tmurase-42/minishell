/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:59 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/09 23:26:26 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_env_value(t_env *env, const char *new_value)
{
	char	*old_value;

	old_value = env->value;
	if (new_value)
	{
		if (!(env->value = ft_strdup(new_value)))
			ft_error(NULL, NULL);
	}
	else
		env->value = NULL;
	ft_free_char(&old_value);
}

void		ft_env_update(const char *key, const char *value, t_env *envs)
{
	t_env	*env;

	if (!key)
		return ;
	if (!(env = ft_env_get(key, envs)))
	{
		env = ft_env_create((char *)key);
		ft_env_add(env, &envs);
	}
	set_env_value(env, value);
}
