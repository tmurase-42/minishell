/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:56:52 by mitchiwaki        #+#    #+#             */
/*   Updated: 2021/03/31 19:35:24 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = buf1;
	tmp2 = (char *)buf2;
	if (buf1 != NULL || buf2 != NULL)
	{
		while (n-- > 0)
			*tmp1++ = *tmp2++;
	}
	return (buf1);
}

/*
** 【概要】
** 	nサイズ分、配列buf2の値を配列buf1の先頭からコピーする。
** 【処理】
** 	引数の配列がNULLじゃない場合（値がある場合）は、nが0になるまでコピーし続ける。
** 	コピー完了後、buf1をreturnする。
*/
