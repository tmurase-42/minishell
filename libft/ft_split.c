/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 22:49:39 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 20:14:08 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char *str, char c)
{
	int		i;
	int		cnt;

	cnt = 0;
	i = 0;
	while (str[i] == c)
		i++;
	if (str[i] != '\0')
		cnt++;
	while (i < (int)ft_strlen(str))
	{
		while (str[i] == str[i + 1])
			i++;
		if (str[i] == c && str[i + 1] != '\0')
			cnt++;
		i++;
	}
	return (cnt);
}

static char	*stradd(char *s, char c)
{
	size_t		i;
	char		*tmp;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	tmp = ft_substr(s, 0, i);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static void	*strfree(char **str, int index)
{
	while (index--)
		free(str[index]);
	free(str);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		element;
	int		index;

	str = NULL;
	if (!s)
		return (NULL);
	element = (count((char *)s, c));
	str = ft_calloc(element + 1, sizeof(char *));
	if (!str)
		return (NULL);
	index = 0;
	while ((*s != '\0' && index < element))
	{
		while (*s == c && *s != '\0')
			s++;
		str[index] = stradd((char *)s, c);
		if (!(str[index]))
			return (strfree(str, index));
		while (*s != c && *s != '\0')
			s++;
		index++;
	}
	str[index] = (NULL);
	return (str);
}
