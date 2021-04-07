/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:31:37 by tmurase           #+#    #+#             */
/*   Updated: 2020/10/07 22:07:05 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

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
	if (!(copy = (char *)malloc(sizeof(char) * cp_len + 1)))
		return (NULL);
	ft_memcpy(copy, s1, s1_len + 1);
	ft_memcpy(copy + s1_len, s2, s2_len + 1);
	return (copy);
}

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	char *tmp1;
	char *tmp2;

	tmp1 = buf1;
	tmp2 = (char *)buf2;
	if (buf1 != NULL || buf2 != NULL)
	{
		while (n > 0)
		{
			*tmp1++ = *tmp2++;
			n--;
		}
	}
	return (buf1);
}

char	*ft_strdup(const char *string)
{
	size_t		i;
	char		*tmp;

	i = ft_strlen(string) + 1;
	if (!(tmp = (char *)malloc((i))))
		return (NULL);
	ft_memcpy(tmp, string, i);
	return (tmp);
}




char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
