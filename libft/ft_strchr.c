/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 23:29:46 by mitchiwaki        #+#    #+#             */
/*   Updated: 2021/07/28 22:44:06 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (*s == c)
		return ((char *)s);
	while (*s++)
	{
		if (*s == c)
			return ((char *)s);
	}
	return (NULL);
}

/*
** 【概要】
** 	配列sの中から値cを検索する関数。
** 【処理】
** 	配列のアドレスをインクリメントし続け、値cと一致した際に配列sのアドレスを返す。
** 	ない場合はNULLを返す。
*/
