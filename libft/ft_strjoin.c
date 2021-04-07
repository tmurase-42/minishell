/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 19:11:35 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 20:18:10 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;
	size_t	s1_len;
	size_t	s2_len;
	size_t	cp_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	cp_len = s1_len + s2_len;
	copy = (char *)malloc(sizeof(char) * cp_len + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s1, cp_len + 1);
	ft_strlcpy(copy + s1_len, s2, cp_len + s1_len + 1);
	return (copy);
}

/*
** 【概要】
** 	二つの文字列を連結した文字列を返却する関数。
** 【処理】
** 	二つの文字列の長さ分のメモリを確保して、s1の値をコピーした後にs2の値を連結させる。
*/
