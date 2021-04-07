/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:39:21 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 20:37:12 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;
	int		i;

	start = 0;
	if (!s1 || !set)
		return (ft_strdup(""));
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = end - start + 1;
	while (i--)
		str[i] = s1[start + i];
	str[end - start] = '\0';
	return (str);
}

/*
** 【概要】
** 	setされた文字列ではないものを抜き出す関数。
** 【処理】
** 	抜き出したい文字列の最初と最後のアドレスを検索して、抜き出したい文字列の長さ分、mallocで
** 	用意した配列にコピーさせている。
*/
