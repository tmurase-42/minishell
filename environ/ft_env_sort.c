/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:35:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 19:05:06 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	**ft_env_sort()
{
	extern t_mshl_data	*g_mshl_data;
	t_env				**array;
	int					array_len;
	int					i;
	int					j;
	t_env				*tmp;

	i = 0;
	array = ft_env_array(g_mshl_data->envs);
	array_len = ft_env_len(*array);
	while(array_len >= i)
	{
		j = 0;
		while(array[j])
		{
			if (array[j] && array[j + 1]
				&& ft_strncmp(array[j]->key, array[j + 1]->key, MAX(ft_strlen(array[j]->key), ft_strlen(array[j + 1]->key))) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return array;
}
