/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:41 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/07 18:48:40 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env		*ft_env_init(char **environ)
{
	size_t	i;
	t_env	*envs;
	t_env	*current;

	envs = NULL;
	i = 0;
	while (environ[i])
	{
		current = ft_env_create(environ[i]);
		if (current)
			ft_env_add(current, &envs);
		i++;
	}
	return (envs);
}