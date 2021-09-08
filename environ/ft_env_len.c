/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:39:25 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 18:40:59 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_env_len(t_env *envs)
{
	size_t	len;

	len = 0;
	while (envs)
	{
		len++;
		envs = envs->next;
	}
	return (len);
}
