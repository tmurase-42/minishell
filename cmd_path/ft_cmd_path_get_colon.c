/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path_get_colon.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:55:36 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 23:01:07 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*strdup_colon_unit(char *unit, const char *default_value)
{
	char *res;

	if (!unit)
		return (NULL);
	if (ft_strlen(unit) == 0)
	{
		if (!(res = ft_strdup(default_value)))
			ft_error(NULL, EXIT_FAILURE);
	}
	else
	{
		if (!(res = ft_strdup(unit)))
			ft_error(NULL, EXIT_FAILURE);
	}
	return (res);
}

static char	**allocate_colon_unit_parent(const char *str)
{
	size_t	index;
	size_t	colon_count;
	char	**res;

	index = 0;
	colon_count = 0;
	while (str[index])
	{
		if (str[index] == ':')
			colon_count++;
		index++;
	}
	if (!(res = malloc(sizeof(char *) * (colon_count + 2))))
		ft_error(NULL, EXIT_FAILURE);
	res[colon_count + 1] = NULL;
	return (res);
}

char	**ft_cmd_path_get_colon(const char *str, const char *default_value)
{
	char	**res;
	size_t	index;
	char	*copied_str;
	char	*unit_start;
	char	*unit_end;

	index = 0;
	res = allocate_colon_unit_parent(str);
	if (!(copied_str = ft_strdup(str)))
		ft_error(NULL, EXIT_FAILURE);
	unit_start = copied_str;
	unit_end = ft_strchr(unit_start, ':');
	while (unit_end)
	{
		*unit_end = '\0';
		res[index] = strdup_colon_unit(unit_start, default_value);
		unit_start = unit_end + 1;
		unit_end = ft_strchr(unit_start, ':');
		index++;
	}
	res[index] = strdup_colon_unit(unit_start, default_value);
	ft_free_char(&copied_str);
	return (res);
}
