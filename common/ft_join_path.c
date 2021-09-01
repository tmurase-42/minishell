/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:45:56 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 23:01:06 by tdofuku          ###   ########.fr       */
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
	if (!(tmp = ft_strjoin(prev, "/")))
		ft_error(NULL, EXIT_FAILURE);
	index = ft_strlen(tmp);
	if (index >= 2 && tmp[index - 2] == '/')
		tmp[index - 1] = '\0';
	if (!(res = ft_strjoin(tmp, next)))
		ft_error(NULL, EXIT_FAILURE);
	free(tmp);
	return (res);
}
