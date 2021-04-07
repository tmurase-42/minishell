/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 23:13:49 by mitchiwaki        #+#    #+#             */
/*   Updated: 2020/07/07 22:29:11 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(dest);
	k = ft_strlen((char *)src);
	j = 0;
	if (i >= size)
		return (k + size);
	if (size == 0)
		return (k);
	while (src[j] != '\0' && j < size - i - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (i + k);
}

/*
** 【概要】
** 	最大size-destの長さ-1分をdestの最後からsrcの値を連結する。
** 【処理】
** 	引数二つ分の配列長さを計り、配列srcのインデックス番号がsize-destの長さ-1を
** 	超えるまでsrcの値をdestの末尾にコピーし続ける。
*/
