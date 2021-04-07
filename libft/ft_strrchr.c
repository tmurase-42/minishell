/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 00:12:38 by mitchiwaki        #+#    #+#             */
/*   Updated: 2020/07/12 22:27:12 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*p;
	int				s_len;

	p = (unsigned char *)s;
	s_len = ft_strlen((char *)s) + 1;
	while (s_len--)
	{
		if (p[s_len] == (char)c)
			return ((char *)&s[s_len]);
	}
	return (NULL);
}
