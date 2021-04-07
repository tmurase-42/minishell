/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 21:09:15 by mitchiwaki        #+#    #+#             */
/*   Updated: 2020/07/07 22:03:34 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	if (src == NULL)
		return (0);
	while (src[count] != '\0')
		count++;
	if (size != 0)
	{
		while (src[index] != '\0' && (index < (size - 1)))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (count);
}

/*
** 【概要】
** 	size-1文字まで、配列srcの値を配列dstへコピーする。
** 【処理】
** 	まず返り値用のcountの数（srcの長さ）をカウントする。次にインクリメントされていくsrcのイン
** 	デックス番号がsize-1より大きくなるまで、srcの値をdstへコピーし続ける。コピー完了後、ヌル
** 	文字を代入する。
*/
