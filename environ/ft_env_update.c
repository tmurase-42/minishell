/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:59 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 02:41:43 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_env_value(t_env *env, const char *new_value)
{
	char	*old_value;

	old_value = env->value;
	if (new_value)
	{
		env->value = ft_strdup(new_value);
		if (env->value == NULL)
			ft_error(NULL, NULL, EXIT_FAILURE);
	}
	else
		env->value = ft_strdup("\0");
	ft_free_char(&old_value);
}

void	ft_env_update(const char *key, const char *value)
{
	extern t_mshl_data	*g_mshl_data;
	t_env				*env;

	if (!key || !*key)
		return ;
	env = ft_env_get(key, g_mshl_data->envs);
	if (env == NULL)
	{
		env = ft_env_create((char *)key);
		ft_env_add(env, &g_mshl_data->envs);
	}
	set_env_value(env, value);
}
