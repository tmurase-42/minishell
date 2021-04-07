/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 13:34:08 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 19:27:18 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)buf;
	while (n--)
	{
		if (*p != (unsigned char)ch)
			p++;
		else
			return (p);
	}
	return (NULL);
}

/*
** 【概要】
** 	配列bufからnバイト分、値chが配列bufにあるかどうか検索する関数。
** 【処理】
** 	省略。
*/
