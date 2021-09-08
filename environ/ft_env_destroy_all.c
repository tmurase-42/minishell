/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_destroy_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:33 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 11:41:18 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_destroy_all(t_env *env)
{
	t_env				*tmp;

	while(env)
	{
		tmp = env;
		ft_free_char(&(env->value));
		ft_free_char(&(env->key));
		free(env);
		env = tmp->next;
	}
	free(env);
}
