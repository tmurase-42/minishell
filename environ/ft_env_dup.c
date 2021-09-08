/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:43:38 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 23:48:39 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_env_dup(t_env *env)
{
	t_env	*new_env;

	if (env == NULL || env->key == NULL || *(env->key) == '\0')
		return NULL;
	new_env = ft_env_create(env->key);
	new_env->value = ft_strdup(env->value);
	new_env->next = env->next;
	new_env->is_env = TRUE;
	return (new_env);
}
