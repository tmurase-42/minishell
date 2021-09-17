/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print_envs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:33:24 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 01:39:15 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	get_len_to_alloc(const char *str, const char *esc)
{
	size_t	index;
	size_t	res;

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
	size_t	res_index;
	size_t	index;

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
	new_len = get_len_to_alloc(str, esc_chars);
	new_str = malloc(sizeof(char) * new_len + 1);
	if (new_str == NULL)
		ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
	copy_escaped_value(str, esc_chars, new_str);
	return (new_str);
}

static void	print_env(t_env *env)
{
	char	*escaped_value;

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

int	ft_export_print_envs(void)
{
	t_env	**array;
	int		i;

	i = 0;
	array = ft_env_sort();
	while (array[i])
	{
		print_env(array[i]);
		i++;
	}
	i = 0;
	free(array);
	return (EXIT_SUCCESS);
}
