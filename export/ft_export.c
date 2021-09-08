/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:50:48 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/07 22:22:20 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define EQUAL 1
#define PLUS_EQUAL 2

static t_bool	is_valid_key(char *key)
{
	size_t	i;

	i = 0;
	if (key[i] != '_' && !ft_isalpha(key[i]))
		return (FALSE);
	i++;
	while (key[i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

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
		if (is_valid_key(ret))
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



static int		set_envs(t_cmd *cmd)
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

static size_t	get_len_to_alloc(const char *str, const char *esc)
{
	size_t index;
	size_t res;

	index = 0;
	res = 0;
	while (str[index] != 0)
	{
		if (ft_strchr(esc, str[index]) != NULL)
			res++;
		res++;
		index++;
	}
	return (res);
}

static void	copy_escaped_value(const char *src, const char *esc, char *dest)
{
	size_t res_index;
	size_t index;

	index = 0;
	res_index = 0;
	while (src[index] != 0)
	{
		if (ft_strchr(esc, src[index]) != NULL)
		{
			dest[res_index] = '\\';
			res_index++;
		}
		dest[res_index] = src[index];
		res_index++;
		index++;
	}
	dest[res_index] = '\0';
}

static char	*get_escaped_value(const char *str)
{
	char	*esc_chars;
	int		new_len;
	char	*new_str;

	esc_chars = "\"\\$";
	// if (state == STATE_IN_GENERAL)
		// esc_chars = "\'\"\\$|;><";
	// if (is_env == TRUE)
		// esc_chars = "\"\\$`";
	new_len = get_len_to_alloc(str, esc_chars);
	if (!(new_str = malloc(sizeof(char) * new_len + 1)))
	{
		// error
	}
	copy_escaped_value(str, esc_chars, new_str);
	return (new_str);
}

static void	print_env(t_env *env)
{
	char	*escaped_value;

	if (env->is_env == FALSE)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value)
	{
		escaped_value = get_escaped_value(env->value);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int			print_envs()
{
	extern t_mshl_data	*g_mshl_data;
	t_env			*current_env;

	current_env = g_mshl_data->envs;
	// env_mergesort(&envs, compare_env);
	while (current_env)
	{
		print_env(current_env);
		current_env = current_env->next;
	}
	return (EXIT_SUCCESS);
}

int ft_export(t_cmd *cmd)
{
	if (cmd->argc == 1)
	{
		return (print_envs());
	}
	else
	{
		return (set_envs(cmd));
	}
	return (EXIT_SUCCESS);
}
