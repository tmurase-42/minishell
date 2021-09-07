/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:50:48 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/07 15:40:06 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define EQUAL 1
#define PLUS_EQUAL 2

static char	*get_value(char *str)
{
	return ft_strchr(str, '=') + 1;
}

static char	*get_key(char *str)
{
	int		i;
	char 	*str1;
	char	*ret;


	str1 = ft_strchr(str, '=');
	i = 0;
	if (str1)
	{
		while( str[i] != '\0' && str[i] != '=')
			i++;
		ret = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy(ret, str, i + 1);
		return ret;
	}
	return NULL;
}

static int	is_sep_equal(char *str)
{
	char 	*str1;

	str1 = ft_strchr(str, '=');
	if (str1)
		return EQUAL;
	return FALSE;
}

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

static int		set_envs(t_cmd *cmd)
{
	char	*key;
	char	*value;
	int		ret;
	t_token	*token;

	ret = EXIT_SUCCESS;
	value = NULL;
	key = NULL;
	token = cmd->args->next;
	while (token)
	{
		if ((key = get_key(token->data)))
		{
			value = get_value(token->data);
			if (is_valid_key(key))
			{
				if (is_sep_equal(token->data) == EQUAL)
					ft_env_update(key, value);
				else {
					ft_error_display("export", token->data, EXIT_FAILURE);
					ret = EXIT_FAILURE;
				}
			}
			else
			{
				ft_error_display("minishell", "bad assignment", EXIT_FAILURE);
				ret = EXIT_FAILURE;
			}
			free(key);
		}
		token = token->next;
	}
	return (ret);
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
