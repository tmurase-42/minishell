/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 19:27:34 by tmurase           #+#    #+#             */
/*   Updated: 2020/07/08 01:08:16 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;
	int	s_len;

	if (s == NULL)
		return ;
	s_len = ft_strlen(s);
	i = 0;
	while (i < s_len)
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
