/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 13:54:53 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 19:47:33 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int val, size_t len)
{
	unsigned char	*ptr;

	ptr = buf;
	while (len > 0)
	{
		*ptr = val;
		len--;
		ptr++;
	}
	return (buf);
}

/*
** 【概要】
** 	指定したlenバイト分、valの値をbufの先頭からセットしていく関数。
** 【処理】
** 	省略。
*/
