/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:13:32 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/05 18:43:12 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

#define EXPANSION -36
typedef struct	s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

static t_token	*get_first_token(t_token *tokens)
{
	t_token	*target;

	if (!tokens)
		return (NULL);
	target = tokens;
	while (target->prev)
		target = target->prev;
	return (target);
}

static int	expand_str(t_token *t, int i, char **ret)
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
	// printf("ft_expand: expand_str: j: %d\n", j);
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

static int	expand_args(const char *str, int i, char **ret)
{
	extern t_mshl_data	*g_mshl_data;
	int	j;

	j = (int)*str + i + (int)**ret + g_mshl_data->argc;

	j = 1;
	return (j);
}

static char *create_env_expanded_str(t_token *t)
{
	int		i;
	char	*ret;

	i = 0;
	// ret = NULL;


	ret = ft_calloc(sizeof(char*), 1);

	while(t->data[i])
	{
		if (t->data[i] == '$' && t->data[i + 1] == '0')
		{
			i++;
			// プログラム名を返す
		}
		else if (t->data[i] == '$' && ft_isdigit(t->data[i + 1]))
		{
			i++;
			i += expand_args(t->data, i, &ret);
		}
		else if (t->data[i] == '$' && t->data[i + 1] == '?')
		{
			i++;
			i += expand_exit_status(&ret);
		}
		else if (t->data[i] == '$' && t->data[i + 1] != '\0' && t->data[i + 1] != ' ')
		{
			i++;
			i += expand_str(t, i, &ret);
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


void			ft_expand(t_cmd *cmd)
{
	char	*new_str;
	t_token	*token;

	// esc_chars = "\"\\$";
	// if (state == STATE_IN_GENERAL)
		// esc_chars = "\'\"\\$|;><";
	// if (is_env == TRUE)
		// esc_chars = "\"\\$`";
	if (!cmd->args || (cmd->args && cmd->args->data == NULL))
		return ;
	token = get_first_token(cmd->args);
	new_str = NULL;
	while (token)
	{
		if (token->type == CHAR_QUOTE || token->type == CHAR_EMPTY)
		{
			token = token->next;
			continue ;
		}
		new_str = create_env_expanded_str(token);
		if (*new_str)
		{
			// printf("ft_expand: new_str: %s\n", new_str);
			free(token->data);
			token->data = new_str;
		}
		else
		{
			//printf("ft_expand: new_str: %s\n", new_str);
			free(token->data);
			token->data = new_str;
			ft_token_destroy(token, &cmd->args);
			// printf("ft_felkfae\n");
			// ft_token_print(cmd->args);
		}
		token = token->next;
	}
	return ;
}
