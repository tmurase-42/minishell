/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:33:29 by tdofuku           #+#    #+#             */
/*   Updated: 2021/07/23 13:29:13 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_env(t_env *env)
{
	if (env->value == NULL)
		return ;
	if (env->is_env == FALSE)
		return ;
	ft_putstr_fd(env->key, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putendl_fd(env->value, STDOUT_FILENO);
}

int			ft_env(t_mshl_data *mshl_data)
{
	t_env			*current_env;

	current_env = mshl_data->envs;
	while (current_env)
	{
		print_env(current_env);
		current_env = current_env->next;
	}
	return (EXIT_SUCCESS);
}
