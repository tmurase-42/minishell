/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:53:43 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 02:28:51 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_env_create(char *str)
{
	t_env	*env;
	char	*sep;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
	sep = ft_strchr(str, '=');
	if (!sep)
	{
		env->key = ft_strdup(str);
		if (env->key == NULL)
			ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
		env->value = NULL;
	}
	else
	{
		env->key = ft_substr(str, 0, sep - str);
		env->value = ft_strdup(sep + 1);
		if (env->key == NULL || env->value == NULL)
			ft_error(NULL, NULL, EXIT_FAILURE);
	}
	env->is_env = TRUE;
	env->next = NULL;
	return (env);
}
