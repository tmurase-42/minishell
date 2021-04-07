/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:56:50 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/30 09:27:34 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef GET_NEXT_LINE_H
#	define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFFER_SIZE 100

size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memcpy(void *buf1, const void *buf2, size_t n);
char		*ft_strdup(const char *string);
char		*ft_strchr(const char *s, int c);
int			get_next_line(int fd, char **line);

#	endif
