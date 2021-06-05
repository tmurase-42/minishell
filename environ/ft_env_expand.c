/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:26:01 by tdofuku           #+#    #+#             */
/*   Updated: 2021/06/05 18:35:22 by tdofuku          ###   ########.fr       */
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

// int		ret_size(int ret)
// {
// 	char	*tmp;
// 	int		ret_len;

// 	tmp = ft_itoa(ret);
// 	ret_len = ft_strlen(tmp);
// 	ft_memdel(tmp);
// 	return (ret_len);
// }

// int		get_var_len(const char *arg, int pos, t_env *env, int ret)
// {
// 	char	var_name[BUFF_SIZE];
// 	char	*var_value;
// 	int		i;

// 	i = 0;
// 	if (arg[pos] == '?')
// 		return (ret_size(ret));
// 	if (ft_isdigit(arg[pos]))
// 		return (0);
// 	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
// 	{
// 		var_name[i] = arg[pos];
// 		pos++;
// 		i++;
// 	}
// 	var_name[i] = '\0';
// 	var_value = get_env_value(var_name, env);
// 	i = ft_strlen(var_value);
// 	ft_memdel(var_value);
// 	return (i);
// }

static	int	get_len_to_alloc2(const char *str, t_command *command_info)
{
	int		i;
	int		size;
	t_env	*env;
	char	*exit_status;

	i = 0;
	size = 0;
	env = NULL;
	exit_status = NULL;

	while(str[i])
	{
		if (str[i] == '$' && str[i+1] != '?')
		{
			if ((env = ft_env_get(str + i, command_info->envs)))
			{
				size += ft_strlen(env->key);
				i += (ft_strlen(env->key) + 1);
			}
		}
		else if (str[i] == '$' && str[i+1] == '?')
		{
			if ((exit_status = ft_itoa(command_info->exit_status)))
			{
				size += ft_strlen(exit_status);
				i += (ft_strlen(exit_status) + 2);
				free(exit_status);
			}
			else
			{
				// error
			}
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

static	int create_expanded_str2(char *str, t_command *command_info)
{
	int		i;
	t_env	*env;
	char	*exit_status;

	i = 0;
	env = NULL;
	exit_status = NULL;

	while(str[i])
	{
		if (str[i] == '$' && str[i+1] != '?')
		{
			if ((env = ft_env_get(str + i, command_info->envs)))
			{
				i += ft_strlcpy(str+i, env->value, ft_strlen(env->value));
			}
		}
		else if (str[i] == '$' && str[i+1] == '?')
		{
			if ((exit_status = ft_itoa(command_info->exit_status)))
			{
				i += ft_strlcpy(str+i, exit_status, ft_strlen(exit_status));
				free(exit_status);
			}
			else
			{
				// error
			}
		}
		{
			i += ft_strlcpy(str+i, env->value, 1);
		}
	}
	return (i);
}

char			*ft_env_expand(char *str, t_command *command_info)
{
	int		new_len;
	char	*new_str;

	// esc_chars = "\"\\$";
	// if (state == STATE_IN_GENERAL)
		// esc_chars = "\'\"\\$|;><";
	// if (is_env == TRUE)
		// esc_chars = "\"\\$`";

	new_len = get_len_to_alloc2(str, command_info);
	if (!(new_str = malloc(sizeof(char) * new_len + 1)))
	{
		// error
	}
	create_expanded_str2(new_str, command_info);
	return (new_str);
}
