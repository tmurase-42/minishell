/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:53:43 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 22:48:11 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_env_create(char *str)
{
	t_env	*env;
	char	*sep;

	if (!(env = malloc(sizeof(t_env))))
		ft_error(NULL, NULL, EXIT_FAILURE);
	sep = ft_strchr(str, '=');
	if (!sep)
	{
		if (!(env->key = ft_strdup(str)))
			ft_error(NULL, NULL, EXIT_FAILURE);
		env->value = NULL;
	}
	else
	{
		if (!(env->key = ft_substr(str, 0, sep - str)) ||
			!(env->value = ft_strdup(sep + 1)))
			ft_error(NULL, NULL, EXIT_FAILURE);
	}
	env->is_env = TRUE;
	env->next = NULL;
	return (env);
}
