/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:35:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 16:54:59 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_env_sort()
{
	extern t_mshl_data	*g_mshl_data;
	char				**array;
	int					array_len;
	int					i;
	int					j;
	char				*tmp;

	i = 0;
	array = ft_env_array(g_mshl_data->envs);
	array_len = ft_strlen(*array);
	while(array_len >= i)
	{
		j = 0;
		while(array[j])
		{
			if (array[j] && array[j + 1] && ft_strncmp(array[j], array[j + 1], MAX(ft_strlen(array[j]), ft_strlen(array[j + 1]))) > 0)
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
