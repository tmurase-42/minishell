/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:52:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/19 15:06:29 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_dup_str(char **split_path, int i, int count)
{
	i++;
	while (split_path[i + 1] != NULL)
	{
		free(split_path[i]);
		split_path[i] = ft_strdup(split_path[i + 1]);
		i++;
	}
	free(split_path[count]);
	split_path[(count)] = NULL;
	count--;
	return (count);
}

void	ft_check_dup_str(char **split_path)
{
	int		count;
	int		i;
	int		compare_result;
	size_t	len;

	count = 0;
	i = 0;
	compare_result = 0;
	len = 0;
	while (split_path[count + 1])
		count++;
	while (split_path[i + 1])
	{
		len = ft_strlen(split_path[i]);
		compare_result = ft_strncmp(split_path[i], split_path[i + 1], len);
		if (compare_result == 0)
		{
			count = ft_dup_str(split_path, i, count);
			i = 0;
			continue ;
		}
		i++;
	}
}

void	ft_skip_dot(char **split_path, size_t i, size_t *dot_count, int flag)
{
	size_t	count;

	count = 0;
	while (split_path[count])
		count++;
	while (split_path[i] && i < count - 1)
	{
		free(split_path[i]);
		split_path[i] = ft_strdup(split_path[i + 1]);
		i++;
	}
	free(split_path[i]);
	split_path[i] = NULL;
	(void)flag;
	(*dot_count)++;
}

char	**ft_skip_and_count_dot(char **split_path, size_t *dot_count,
														size_t *dot_dot_count)
{
	int	i;

	i = 0;
	while (split_path[i])
	{
		if (ft_strncmp("..", split_path[i], 2) == 0)
			ft_skip_dot(split_path, i, dot_dot_count, 0);
		else if (ft_strncmp(".", split_path[i], 1) == 0)
			ft_skip_dot(split_path, i, dot_count, 1);
		else
			i++;
	}
	if ((*dot_dot_count) > 0)
		ft_check_dup_str(split_path);
	return (split_path);
}

char	*ft_convert_path(char **split_path)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	str = ft_strdup("/");
	while (split_path[i])
	{
		free(tmp);
		tmp = ft_strdup(str);
		free(str);
		str = ft_strjoin(tmp, split_path[i]);
		if (split_path[i + 1] != NULL)
		{
			free(tmp);
			tmp = ft_strdup(str);
			free(str);
			str = ft_strjoin(tmp, "/");
		}
		i++;
	}
	ft_safe_free_split(&split_path);
	free(tmp);
	return (str);
}
