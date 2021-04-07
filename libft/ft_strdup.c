/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:48:12 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 20:16:04 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	size_t		i;
	char		*tmp;

	i = ft_strlen(string) + 1;
	tmp = (char *)malloc((i));
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, string, i);
	return (tmp);
}

/*
** 【概要】
** 	引数の文字列を複製する関数。
** 【処理】
** 	mallocで用意した配列と引数の配列を引数の長さ分コピーさせる。
*/
