/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:34:27 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 08:31:39 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tmp;

	tmp = (char *)malloc((nmemb * size));
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, (nmemb * size));
	return (tmp);
}

/*
** 【概要】
** 	nmembバイト分のメモリをsize個用意する関数。
** 【処理】
** 	mallocした後に0埋めする。
*/
