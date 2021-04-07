/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 20:44:55 by mitchiwaki        #+#    #+#             */
/*   Updated: 2021/03/31 19:39:13 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *buf1, const void *buf2, size_t n)
{
	char		*tmp1;
	const char	*tmp2;
	char		*lasttmp1;
	const char	*lasttmp2;

	tmp1 = buf1;
	tmp2 = buf2;
	lasttmp1 = tmp1 + (n - 1);
	lasttmp2 = tmp2 + (n - 1);
	if (tmp1 < tmp2)
		while (n-- > 0)
			*tmp1++ = *tmp2++;
	else
		if (buf1 != NULL || buf2 != NULL)
			while (n--)
				*lasttmp1-- = *lasttmp2--;
	return (buf1);
}

/*
**【概要】
** 	配列buf1の先頭から、nバイト分配列buf2の値をコピーする関数。memcpyとの差異は、引数の二つ
** 	配列のアドレスが重ねっている場合でも処理できる点。
** 【処理】
** 	処理を二つに分けている。buf1のアドレスがbuf2よりも先にきている場合は、nが0になるまでコピ
** 	ーする。buf1のアドレスがbu2よりも前にきている場合は、本来最後にコピーするアドレスと、本来
** 	最後にコピーされるアドレスから後ろ順にコピーを行う。
*/
