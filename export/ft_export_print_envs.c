/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print_envs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:33:24 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 16:49:47 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_key(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
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
	}
	free(str);
	return NULL;
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

static void	print_env(char *str)
{
	char	*escaped_value;
	char	*key;
	char	*value;

	value = ft_strchr(str, '=');
	value += 1;
	key = get_key(str);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	if (value)
	{
		escaped_value = get_escaped_value(value);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	free(key);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int			ft_export_print_envs()
{
	char			**array;
	int				i;

	i = 0;
	array = ft_env_sort();
	while (array[i])
	{
		print_env(array[i]);
		i++;
	}
	ft_safe_free_split(&array);
	return (EXIT_SUCCESS);
}
