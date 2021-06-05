/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:50:48 by tdofuku           #+#    #+#             */
/*   Updated: 2021/06/05 14:39:15 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define EQUAL 1
#define PLUS_EQUAL 2

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

static	int	is_sep_equal(char *str)
{
	char 	*str1;
	char	*str2;

	str1 = ft_strchr(str, '=');
	str2 = ft_strnstr(str, "+=", ft_strlen(str));

	if ((str1 && str2 == NULL) || (str1 && str1 < str2))
		return EQUAL;
	else if (str2 != NULL && str2 < str1)
		return PLUS_EQUAL;
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
	value = NULL;
	key = NULL;
	i = 1;
	while (args[i])
	{
		if ((key = get_key(args[i])))
		{
			value = get_value(args[i]);
			if (is_valid_key(key))
			{
				if (is_sep_equal(args[i]) == EQUAL)
					ft_env_update(key, value, envs);
				else if (is_sep_equal(args[i]) == PLUS_EQUAL)
				{
					if (ft_env_get(key, envs))
						ft_env_update(key, ft_strjoin(ft_env_get(key, envs)->value, value), envs);
					else
					{
						ft_error("export", args[i]);
						ret = EXIT_FAILURE;
					}
				}
			}
			else
			{
				ft_error_identifier("export", args[i]);
				ret = EXIT_FAILURE;
			}
		}
		else
		{
			ft_error("export", args[i]);
			ret = EXIT_FAILURE;
		}
		free(key);
		i++;
	}
	return (ret);
}






static void	print_env(t_env *env)
{
	// char	*escaped_value;

	if (env->is_env == FALSE)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	// if (env->value)
	// {
	//	escaped_value = create_expanded_str(env->value, STATE_IN_DQUOTE, TRUE);
	// 	ft_putstr_fd("=\"", STDOUT_FILENO);
	// 	ft_putstr_fd(escaped_value, STDOUT_FILENO);
	// 	ft_putchar_fd('"', STDOUT_FILENO);
	// 	free(escaped_value);
	// }
	ft_putchar_fd('\n', STDOUT_FILENO);
}

// static int	compare_env(t_env *left, t_env *right)
// {
// 	return (ft_strncmp(left->key, right->key, ft_strlen(left->key)));
// }

int			print_envs(t_env *envs)
{
	t_env			*tmp;

	// env_mergesort(&envs, compare_env);
	while (envs)
	{
		print_env(envs);
		tmp = envs->next;
		free(envs);
		envs = tmp;
	}
	return (EXIT_SUCCESS);
}








int ft_export(t_command *command_info)
{
	printf("argc: %d\n", command_info->argc);
	if (command_info->argc == 2)
	{
		return (print_envs(command_info->envs));
	}
	else
	{
		return (set_envs(command_info->argv, command_info->envs));
	}
	return (EXIT_SUCCESS);
}
