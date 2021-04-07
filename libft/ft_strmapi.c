/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 00:43:23 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 20:23:35 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		s_len;
	int		i;
	char	*iterate_str;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen((char *)s);
	i = 0;
	iterate_str = (char *)malloc((s_len + 1) * sizeof(char));
	if (!iterate_str)
		return (NULL);
	while (i < s_len)
	{
		iterate_str[i] = f(i, s[i]);
		i++;
	}
	iterate_str[i] = '\0';
	return (iterate_str);
}

/*
** 【概要】
** 	引数の文字列に関数fを噛ませた結果を別メモリで確保した文字列として返す関数。
** 【処理】
** 	引数の文字列の長さを計り、mallocで確保したメモリに関数fを実行させた結果を代入している。
*/
