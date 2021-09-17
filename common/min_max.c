/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 02:52:01 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 02:55:09 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

t_bool	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}
