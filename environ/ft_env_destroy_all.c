/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_destroy_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 18:40:59 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_destroy_all(t_env *env)
{
	t_env	*tmp;

	if (env == NULL)
		return ;
	while (env)
	{
		tmp = env;
		free(env->value);
		free(env->key);
		free(env);
		env = tmp->next;
	}
	free(env);
}
