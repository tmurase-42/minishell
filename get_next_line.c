/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:22:47 by tmurase           #+#    #+#             */
/*   Updated: 2020/08/10 00:39:04 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


static int				save_to_line(char **save, int fd, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while (save[fd][len] && save[fd][len] != '\n')
		len++;
	if (save[fd][len] == '\n')
	{
		save[fd][len] = '\0';
		*line = ft_strdup(save[fd]);
		tmp = ft_strdup(&save[fd][len + 1]);
		free(save[fd]);
		save[fd] = tmp;
	}
	else
	{
		*line = ft_strjoin(save[fd], "");
		free(save[fd]);
		save[fd] = NULL;
		return (0);
	}
	return (1);
}

static int				return_err(char **line, ssize_t filesize)
{
	if (filesize < 0)
		return (-1);
	*line = ft_strdup("");
	return (0);
}

static int				read_to_save(int fd, char **line,
														char **save, char *buf)
{
	char		*temp;
	ssize_t		filesize;

	while ((filesize = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[filesize] = '\0';
		if (save[fd] == NULL)
			save[fd] = ft_strjoin(buf, "");
		else
		{
			temp = ft_strjoin(save[fd], buf);
			free(save[fd]);
			save[fd] = temp;
		}
		if (ft_strchr(save[fd], '\n'))
			break ;
	}
	free(buf);
	if (filesize < 0 || (filesize == 0 && save[fd] == NULL))
		return (return_err(line, filesize));
	return (save_to_line(save, fd, line));
}


#include <stdio.h>
int						get_next_line(int fd, char **line)
{
	static char	*save[1024];
	char		*buf;
	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	return (read_to_save(fd, line, save, buf));
}
