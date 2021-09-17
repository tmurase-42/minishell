/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:45:56 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 02:46:16 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_path(const char *prev, const char *next)
{
	char	*tmp;
	char	*res;
	size_t	index;

	if (!prev || !next)
		return (NULL);
	tmp = NULL;
	res = NULL;
	tmp = ft_strjoin(prev, "/");
	if (tmp == NULL)
		ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
	index = ft_strlen(tmp);
	if (index >= 2 && tmp[index - 2] == '/')
		tmp[index - 1] = '\0';
	res = ft_strjoin(tmp, next);
	if (res == NULL)
		ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
	free(tmp);
	return (res);
}
