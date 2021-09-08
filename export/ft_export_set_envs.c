/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_set_envs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:31:25 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 10:31:55 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *create_assignment_expression(t_token *token)
{
	char	*str;
	char	*tmp;
	size_t	i;

	str = ft_strdup(token->data);
	i = 0;
	while (token->next && token->next->space_len == 0)
	{
		token = token->next;
		tmp = str;
		str = ft_strjoin(str, token->data);
		if (i > 0)
			free(tmp);
		i++;
	}
	return (str);
}

static char	*get_value(t_token *token)
{
	char	*str;
	char	*ret;

	str = create_assignment_expression(token);
	//printf("ret: %s\n", str);
	if (ft_strchr(str, '='))
	{
		ret = ft_strchr(str, '=') + 1;
		if (ret && *ret)
			return ret;
	}
	free(str);
	return NULL;
}

static char	*get_key(t_token *token)
{
	int		i;
	char	*str;
	char	*ret;

	ret = NULL;
	str = create_assignment_expression(token);
	// printf("str: %s\n", str);
	i = 0;
	if (str && ft_strchr(str, '='))
	{
		while( str[i] != '\0' && str[i] != '=')
			i++;
		ret = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy(ret, str, i + 1);
	}
	if (ret)
	{
		if (ft_env_is_valid_key(ret))
			return ret;
		else
			ft_error_display("minishell", "bad assignment", EXIT_FAILURE);
	}
	free(str);
	return NULL;
}

static void	get_key_value(t_token **token, char **key, char **value)
{
	*key = get_key(*token);
	*value = get_value(*token);
	while ((*token)->next && (*token)->next->space_len == 0)
		*token = (*token)->next;
}

int		ft_export_set_envs(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char	*key;
	char	*value;
	t_token	*token;

	value = NULL;
	key = NULL;
	token = cmd->args->next;
	g_mshl_data->exit_status = EXIT_SUCCESS;
	while (token)
	{
		get_key_value(&token, &key, &value);
		//printf("key: %s$\n", key);
		//printf("value: %s$\n", value);
		if (key)
			ft_env_update(key, value);
		free(key);
		token = token->next;
	}
	return (g_mshl_data->exit_status);
}
