/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:50:48 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/15 17:19:29 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*get_value(char *str)
{
	return ft_strchr(str, '=') + 1;
}

static	char	*get_key(char *str)
{
	char 	*str1;
	char	*str2;

	str1 = ft_strchr(str, '=');
	str2 = ft_strnstr(str, "+=", ft_strlen(str));

	if ((str1 && str2 == NULL) || (str1 && str1 < str2))
		return ft_strtrim(str, ft_strchr(str, '='));
	else if (str2 != NULL && str2 < str1)
		return ft_strtrim(str, ft_strnstr(str, "+=", ft_strlen(str)));
	return NULL;
}

static	t_bool	is_sep_equal(char *str)
{
	char 	*str1;
	char	*str2;

	str1 = ft_strchr(str, '=');
	str2 = ft_strnstr(str, "+=", ft_strlen(str));

	if ((str1 && str2 == NULL) || (str1 && str1 < str2))
		return TRUE;
	else if (str2 != NULL && str2 < str1)
		return FALSE;
	return FALSE;
}

static	t_bool	is_valid_key(char *key)
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

static int		set_envs(char **args, t_env *envs)
{
	size_t	i;
	char	*key;
	char	*value;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	value = NULL;
	while (args[i])
	{
		if ((key = get_key(args[i])) && (value = get_value(args[i])))
		{
			if (is_valid_key(key))
				if (is_sep_equal(args[i]))
				{
					value = ft_strjoin(ft_env_get(key, envs)->value, value);
					ft_env_update(key, value, envs);
					free(value);
				}
				else
					ft_env_update(key, value, envs);
			else
			{
				ft_error("export", args[i]);
				ret = EXIT_FAILURE;
			}
		}
		else
		{
			ft_error("export", args[i]);
			ret = EXIT_FAILURE;
		}
		i++;
	}
	return (ret);
}

int ft_export(t_command *command_info)
{
	if (command_info->argv[1])
	{
		return (set_envs(command_info->argv, command_info->envs));
	}
	else
	{
		// return (print_envs());
	}
	return (EXIT_SUCCESS);
}
