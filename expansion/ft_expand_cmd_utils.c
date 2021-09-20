/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 02:14:42 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/20 13:48:53 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	set_empty_type(int k, t_token *t, char *key, t_bool flag)
{
	if (t->data[k] == '\0' && flag)
		t->type = CHAR_EMPTY;
	return (ft_strlen(key));
}

static int	expand_str(t_token *t, int i, char **ret, t_bool flag)
{
	extern t_mshl_data	*g_mshl_data;
	int					j;
	char				*key;
	char				*tmp;
	t_env				*env;

	j = 0;
	while (ft_isalnum(t->data[i + j]) || t->data[i + j] == '_')
		j++;
	key = ft_substr(t->data, i, j);
	env = ft_env_get(key, g_mshl_data->envs);
	if (env && *ret == NULL)
		*ret = ft_strdup(env->value);
	else if (env)
	{
		tmp = *ret;
		*ret = ft_strjoin(*ret, env->value);
		free(tmp);
	}
	else if (t->type == CHAR_DQUOTE)
		j = set_empty_type((i + j), t, key, flag);
	free(key);
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
	int					dig;
	char				*num;
	char				*tmp;

	dig = 0;
	num = ft_itoa(g_mshl_data->exit_status);
	dig = ft_strlen(num);
	tmp = *ret;
	*ret = ft_strjoin(*ret, num);
	free(num);
	free(tmp);
	return (dig);
}

void	ft_expand_cmd_utils(t_token *t, char **str)
{
	int		i;
	t_bool	first_str_in_quotes_flag;

	i = 0;
	first_str_in_quotes_flag = TRUE;
	while (t->data[i])
	{
		if (t->data[i] == '$' && t->data[i + 1] == '?')
		{
			i++;
			i += (expand_exit_status(str));
		}
		else if (t->data[i] == '$' && t->data[i + 1] != '\0'
			&& t->data[i + 1] != ' ' && ft_isdigit(t->data[i + 1]) == FALSE)
		{
			i++;
			i += expand_str(t, i, str, first_str_in_quotes_flag);
			first_str_in_quotes_flag = FALSE;
		}
		else if (t->data[i] == '$' && t->data[i + 1] == '\0'
			&& t->next && t->next->type == CHAR_EMPTY)
			i++;
		else
			i += copy_char(t->data, i, str);
	}
}
