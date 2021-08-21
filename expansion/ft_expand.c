/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:13:32 by tdofuku           #+#    #+#             */
/*   Updated: 2021/07/29 22:23:47 by tmurase          ###   ########.fr       */
/*   Updated: 2021/08/10 11:21:37 by tdofuku          ###   ########.fr       */
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

static	t_token	*get_first_token(t_token *tokens)
{
	t_token	*target;

	if (!tokens)
		return (NULL);
	target = tokens;
	while (target->prev)
		target = target->prev;
	return (target);
}

// static	int	get_len_with_vars(const char *str, t_mshl_data *mshl_data)
// {
// 	int		i;
// 	int		size;
// 	t_env	*env;
// 	char	*exit_status;

// 	i = 0;
// 	size = 0;
// 	env = NULL;
// 	exit_status = NULL;

// 	while(str[i])
// 	{
// 		if (str[i] == '$' && str[i+1] != '?')
// 		{
// 			i++;
// 			printf("ft_expand: str + i: %s\n", str + i);
// 			if ((env = ft_env_get(str + i, mshl_data->envs)))
// 			{
// 				size += ft_strlen(env->value);
// 				printf("ft_expand: env->value: %s$\n", env->value);
// 				printf("ft_expand: env->key: %s$\n", env->key);
// 				i += (ft_strlen(env->key));
// 			}
// 		}
// 		else if (str[i] == '$' && str[i+1] == '?')
// 		{
// 			i += 2;
// 			if ((exit_status = ft_itoa(mshl_data->exit_status)))
// 			{
// 				size += ft_strlen(exit_status);
// 				i += (ft_strlen(exit_status));
// 				free(exit_status);
// 			}
// 			else
// 			{
// 				// error
// 			}
// 		}
// 		else
// 		{
// 			i++;
// 			size++;
// 		}
// 	}
// 	return (size);
// }



// static	char *create_env_expanded_str(char *str, t_mshl_data *mshl_data)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	t_env	*env;
// 	char	*exit_status;
// 	char	*new_str;
// 	int		new_len;
// 	char	*var_str;

// 	i = 0;
// 	j = 0;
// 	env = NULL;
// 	exit_status = NULL;

// 	printf("ft_expand: str: %s\n", str);
// 	new_len = get_len_with_vars(str, mshl_data);
// 	printf("ft_expand: new_len: %d\n", new_len);
// 	if (!(new_str = ft_calloc(sizeof(char), new_len("malloc error;", str);
// 	while(str[i])
// 	{
// 		// printf("str[%d]: %c\n", i, str[i]);
// 		if (str[i] == '$' && str[i+1] == '?')
// 		{
// 			i++;
// 			if ((exit_status = ft_itoa(mshl_data->exit_status)))
// 			{
// 				j += ft_strlcpy(new_str+j, exit_status, ft_strlen(exit_status) + 1);
// 				i += 2;
// 				free(exit_status);
// 			}
// 			else
// 			{
// 				ft_error("error;", str);
// 			}
// 		}
// 		else if (str[i] == '$' && ft_isdigit(str[i+1]))
// 		{
// 			// 数字の処理
// 		}
// 		else if (str[i] == '$' && str[i+1] == '$')
// 		{
// 			// $$の時の処理
// 		}
// 		else if (str[i] == '$' && str[i+1] != '?')
// 		{

// 			k = 1;
// 			while(str[i + k] && (ft_isalnum(str[i + k]) || str[i + k] == '_'))
// 				k++;
// 			var_str = ft_substr(str, (i + 1), k);

// 			printf("ft_expand: str[%d]: %s\n", i, str + i + 1);
// 			printf("ft_expand: var_str: %s\n", var_str);
// 			if ((env = ft_env_get(var_str, mshl_data->envs)) != NULL)
// 			{
// 				printf("ft_expand: message: env is hit!\n");
// 				printf("ft_expand: message: env->key: %s\n", env->key);
// 				printf("ft_expand: message: env->value: %s\n", env->value);

// 				j += ft_strlcpy(new_str+j, env->value, ft_strlen(env->value) + 1);
// 				i += (ft_strlen(env->key) + 1);
// 				printf("ft_expand: str[%d]: %c\n", i, str[i]);
// 				printf("ft_expand: new_str: %s\n", new_str);
// 			}
// 			else
// 			{
// 				printf("ft_expand: message: env is not hit!\n");
// 				// printf("new_str[%d]: %c\n", j, new_str[j]);
// 				i += k;
// 			}



// 		}
// 		else {
// 			ft_strlcpy(new_str+j, str+i, 2);
// 			// printf("new_str[%d]: %c\n", j, new_str[j]);
// 			i++;
// 			j++;
// 		}
// 	}
// 	return (new_str);
// }



static	int	expand_str(const char *str, int i, char **ret, t_mshl_data *mshl_data)
{
	int		j;
	char	*key;
	char	*tmp;
	t_env	*env;

	if (!str[i])
		return (0);
	j = 0;
	while(ft_isalnum(str[i + j]))
		j++;
	key = ft_substr(str, i, j);
	// printf("ft_expnad: expand_str: key: %s\n", key);
	env = ft_env_get(key, mshl_data->envs);
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

static	int	copy_char(const char *str, int i, char **ret)
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

static	int	expand_specials(const char *str, int i, char **ret, t_mshl_data *mshl_data)
{

	int	j;

	j = (int)*str + i + (int)**ret + mshl_data->argc;

	j = 1;
	return (j);
}

static	int	expand_args(const char *str, int i, char **ret, t_mshl_data *mshl_data)
{

	int	j;

	j = (int)*str + i + (int)**ret + mshl_data->argc;

	j = 1;
	return (j);
}






static	char *create_env_expanded_str(const char *str, t_mshl_data *mshl_data)
{
	int		i;
	char	*ret;

	i = 0;
	// ret = NULL;


	ret = ft_calloc(sizeof(char*), 1);

	while(str[i])
	{
		if (str[i] == '$' && str[i + 1] == '0')
		{
			i++;
			// プログラム名を返す
		}
		else if (str[i] == '$' && ft_isdigit(str[i + 1]))
		{
			i++;
			i += expand_args(str, i, &ret, mshl_data);
		}
		else if (str[i] == '$' && (str[i + 1] == '{' || str[i + 1] == '@' || str[i + 1] == '*' || str[i + 1] == '#' || str[i + 1] == '?' || str[i + 1] == '$' || str[i + 1] == '!' || str[i + 1] == '-'))
		{
			i++;
			i += expand_specials(str, i, &ret, mshl_data);
		}
		else if (str[i] == '$')
		{
			i++;
			i += expand_str(str, i, &ret, mshl_data);
		}
		else
		{
			// printf("ft_expand: str: %s\n", str + i);
			i += copy_char(str, i, &ret);
			// printf("ft_expnad: ret: %s\n", ret);
		}
	}
	return (ret);
}












void			ft_expand(t_cmd *cmd, t_mshl_data *mshl_data)
{
	char	*new_str;
	t_token	*token;


	// esc_chars = "\"\\$";
	// if (state == STATE_IN_GENERAL)
		// esc_chars = "\'\"\\$|;><";
	// if (is_env == TRUE)
		// esc_chars = "\"\\$`";
	if (!cmd->args)
		return ;
	token = get_first_token(cmd->args);
	while (token)
	{
		new_str = create_env_expanded_str(token->data, mshl_data);
		if (*new_str)
		{
			// printf("ft_expand: new_str: %s\n", new_str);
			free(token->data);
			token->data = new_str;
		}
		else
		{
			// printf("ft_expand: new_str: %s\n", new_str);
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
