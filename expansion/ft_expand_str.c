/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 21:31:58 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 21:41:24 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	expand_str(char *str, int i, char **ret)
{
	extern t_mshl_data	*g_mshl_data;
	int		j;
	char	*key;
	char	*tmp;
	t_env	*env;

	if (!str[i])
		return (0);
	j = 0;
	while(ft_isalnum(str[i + j]) || str[i + j] == '_')
		j++;
	key = ft_substr(str, i, j);
	env = ft_env_get(key, g_mshl_data->envs);
	if(env)
	{
		if (*ret == NULL)
			*ret = ft_strdup(env->value);
		else
		{
			tmp = *ret;
			*ret = ft_strjoin(*ret, env->value);
			free(tmp);
		}
	}
	return (j);
}

static int	copy_char(const char *str, int i, char **ret)
{
	char	*c;
	char	*tmp;

	c = ft_substr(str, i, 1);
	if (*ret == NULL)
		*ret = c;
	else
	{
		tmp = *ret;
		*ret = ft_strjoin(*ret, c);
		free(tmp);
		free(c);
	}
	return (1);
}

static int	expand_exit_status(char **ret)
{
	extern t_mshl_data	*g_mshl_data;
	int		dig;
	char	*num;
	char	*tmp;

	dig = 0;
	num = ft_itoa(g_mshl_data->exit_status);
	dig = ft_strlen(num);
	tmp = *ret;
	*ret = ft_strjoin(*ret, num);
	free(num);
	free(tmp);
	return (dig);
}

static char	*create_env_expanded_str(char *str)
{
	extern t_mshl_data	*g_mshl_data;
	int		i;
	char	*ret;

	i = 0;
	ret = ft_calloc(sizeof(char*), 1);

	while(str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			i++;
			i += expand_exit_status(&ret);
		}
		else if (str[i] == '$' && str[i + 1] != '\0'
			&& str[i + 1] != ' ' && ft_isdigit(str[i + 1]) == FALSE)
		{
			i++;
			i += expand_str(str, i, &ret);
		}
		else
		{
			i += copy_char(str, i, &ret);
		}
	}
	return (ret);
}

void		ft_expand_str(char **str)
{
	char	*tmp;

	if (*str == NULL || **str == '\0')
		return ;
	tmp = *str;
	*str = create_env_expanded_str(*str);
	free(*str);
}
