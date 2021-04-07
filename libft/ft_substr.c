/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 22:08:04 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/01 18:45:43 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	s_len;
	size_t	c_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		return (ft_strdup(""));
	if ((s_len - start) < len)
	{
		copy = ft_calloc((s_len - start + 1), sizeof(char));
		c_len = s_len - start;
	}
	else
	{
		copy = ft_calloc(len + 1, sizeof(char));
		c_len = len;
	}
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s + start, c_len);
	copy[c_len] = '\0';
	return (copy);
}
