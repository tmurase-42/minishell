/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:13:32 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 21:31:37 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	expand_str(t_token *t, int i, char **ret, t_bool flag)
{
	extern t_mshl_data	*g_mshl_data;
	int		j;
	char	*key;
	char	*tmp;
	t_env	*env;

	if (!t->data[i])
		return (0);
	j = 0;
	while(ft_isalnum(t->data[i + j]) || t->data[i + j] == '_')
		j++;
	key = ft_substr(t->data, i, j);
	env = ft_env_get(key, g_mshl_data->envs);
	if(env)
	{
		// printf("ft_expnad: expand_str: env->value: %s\n", env->value);
		if (*ret == NULL)
			*ret = ft_strdup(env->value);
		else
		{
			tmp = *ret;
			*ret = ft_strjoin(*ret, env->value);
			free(tmp);
		}
	}
	else if (t->type == CHAR_DQUOTE)
	{
		j = ft_strlen(key);
		if (t->data[i + j] == '\0' && flag)
			t->type = CHAR_EMPTY;
	}
	//printf("ft_expand: expand_str: j: %d\n", j);
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

static char	*create_env_expanded_str(t_token *t)
{
	extern t_mshl_data	*g_mshl_data;
	int		i;
	char	*ret;
	t_bool	first_str_in_quotes_flag;

	i = 0;
	// ret = NULL;
	first_str_in_quotes_flag = TRUE;


	ret = ft_calloc(sizeof(char*), 1);

	while(t->data[i])
	{
		if (t->data[i] == '$' && t->data[i + 1] == '?')
		{
			i++;
			i += expand_exit_status(&ret);
		}
		else if (t->data[i] == '$' && t->data[i + 1] != '\0'
			&& t->data[i + 1] != ' ' && ft_isdigit(t->data[i + 1]) == FALSE)
		{
			i++;
			i += expand_str(t, i, &ret, first_str_in_quotes_flag);
			first_str_in_quotes_flag = FALSE;
		}
		else
		{
			// printf("ft_expand: t->data: %s\n", t->data + i);
			i += copy_char(t->data, i, &ret);
			// printf("ft_expnad: ret: %s\n", ret);
		}
	}
	return (ret);
}

void		ft_expand_cmd(t_cmd *cmd)
{
	char	*new_str;
	t_token	*token;

	if (!cmd->args || (cmd->args && cmd->args->data == NULL))
		return ;
	token = ft_token_get_first(cmd->args);
	new_str = NULL;
	while (token)
	{
		if ((token->type != CHAR_QUOTE && token->type != CHAR_EMPTY))
		{
			new_str = create_env_expanded_str(token);
			free(token->data);
			token->data = new_str;
		}
		token = token->next;
	}
	return ;
}
