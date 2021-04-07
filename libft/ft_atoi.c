/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 20:48:40 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 08:22:46 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int	rtn;
	int	count;

	count = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (ft_strchr(str, '-'))
		count = 1;
	if (*str == '-' || *str == '+')
		str++;
	rtn = 0;
	while (*str != '\0')
	{
		if (*str < 48 || *str > 57)
			break ;
		rtn *= 10;
		rtn += *str - '0';
		str++;
	}
	if (count == 1)
		rtn *= -1;
	return (rtn);
}
