/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 19:19:30 by mitchiwaki        #+#    #+#             */
/*   Updated: 2021/03/31 19:31:56 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = s1;
	p2 = s2;
	while (n != 0)
	{
		if (*p1++ != *p2++)
			return (*--p1 - *--p2);
		n--;
	}
	return (0);
}

/*
** 【概要】
** 	配列s1と配列s2をnバイト分比較する。
** 【処理】
** 	省略
*/
