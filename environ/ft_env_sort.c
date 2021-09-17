/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:35:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 02:37:05 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	bubble_array(t_env **array)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	while (array[i])
	{
		if (array[i] && array[i + 1]
			&& ft_strncmp(array[i]->key, array[i + 1]->key,
				MAX(ft_strlen(array[i]->key),
					ft_strlen(array[i + 1]->key))) > 0)
		{
			tmp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = tmp;
		}
		i++;
	}
}

t_env	**ft_env_sort(void)
{
	extern t_mshl_data	*g_mshl_data;
	t_env				**array;
	int					array_len;
	int					i;

	i = 0;
	array = ft_env_array(g_mshl_data->envs);
	array_len = ft_env_len(*array);
	while (array_len >= i)
	{
		bubble_array(array);
		i++;
	}
	return (array);
}
