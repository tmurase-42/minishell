/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_is_valid_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:08:41 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/19 18:17:01 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_env_is_valid_key(char *key)
{
	size_t	i;

	i = 0;
	if (key == NULL)
		return (FALSE);
	if (key[i] != '_' && !ft_isalpha(key[i]))
		return (FALSE);
	i++;
	while (key[i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
