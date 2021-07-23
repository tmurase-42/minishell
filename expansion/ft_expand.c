/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:13:32 by tdofuku           #+#    #+#             */
/*   Updated: 2021/07/23 13:50:33 by tdofuku          ###   ########.fr       */
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

static	int	get_len_with_vars(const char *str, t_mshl_data *mshl_data)
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
			if ((env = ft_env_get(str + i, mshl_data->envs)))
			{
				size += ft_strlen(env->key);
				i += (ft_strlen(env->key) + 1);
			}
		}
		else if (str[i] == '$' && str[i+1] == '?')
		{
			if ((exit_status = ft_itoa(mshl_data->exit_status)))
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

static	int create_env_expanded_str(char *str, char *new_str, t_cmd *cmd, t_mshl_data *mshl_data)
{
	int		i;
	int		j;
	t_env	*env;
	char	*exit_status;

	i = 0;
	j = 0;
	env = NULL;
	exit_status = NULL;

	while(str[i])
	{
		// printf("str[%d]: %c\n", i, str[i]);
		if (str[i] == '$' && str[i+1] != '?')
		{
			printf("str[%d]: %c\n", i, str[i]);
			if ((env = ft_env_get(str + i + 1, mshl_data->envs)) != NULL)
			{
				printf("env is hit!\n");
				j += ft_strlcpy(new_str+j, env->value, ft_strlen(env->value) + 1);
				i += (ft_strlen(env->key) + 1);
				printf("str[%d]: %c\n", i, str[i]);
				printf("new_str[%d]: %c\n", j-1, new_str[j-1]);
			}
			else
			{
				ft_strlcpy(new_str+j, str+i, 2);
				// printf("new_str[%d]: %c\n", j, new_str[j]);
				i++;
				j++;
			}
		}
		else if (str[i] == '$' && str[i+1] == '?')
		{
			i++;
			if ((exit_status = ft_itoa(mshl_data->exit_status)))
			{
				j += ft_strlcpy(new_str+j, exit_status, ft_strlen(exit_status) + 1);
				i += 2;
				free(exit_status);
			}
			else
			{
				ft_error("error;", cmd->args->data);
			}
		} else {
			ft_strlcpy(new_str+j, str+i, 2);
			// printf("new_str[%d]: %c\n", j, new_str[j]);
			i++;
			j++;
		}
	}
	return (i);
}

char			*ft_expand(char *str, t_cmd *cmd, t_mshl_data *mshl_data)
{
	int		new_len;
	char	*new_str;


	// esc_chars = "\"\\$";
	// if (state == STATE_IN_GENERAL)
		// esc_chars = "\'\"\\$|;><";
	// if (is_env == TRUE)
		// esc_chars = "\"\\$`";

	printf("str: %s\n", str);
	new_len = get_len_with_vars(str, mshl_data);
	if (!(new_str = malloc(sizeof(char) * new_len + 1)))
		ft_error("malloc error;", cmd->args->data);
	create_env_expanded_str(str, new_str, cmd, mshl_data);
	printf("new_str: %s\n", new_str);
	return (new_str);
}
