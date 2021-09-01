/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:45:56 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 17:07:41 by tdofuku          ###   ########.fr       */
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
		ft_error(NULL, NULL, 1);
	index = ft_strlen(tmp);
	if (index >= 2 && tmp[index - 2] == '/')
		tmp[index - 1] = '\0';
	if (!(res = ft_strjoin(tmp, next)))
		ft_error(NULL, NULL, 1);
	free(tmp);
	return (res);
}
