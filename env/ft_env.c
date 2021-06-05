/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:33:29 by tdofuku           #+#    #+#             */
/*   Updated: 2021/06/05 15:02:21 by tdofuku          ###   ########.fr       */
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

int			ft_env(t_command *command_info)
{
	t_env			*current_env;

	current_env = command_info->envs;
	while (current_env)
	{
		print_env(current_env);
		current_env = current_env->next;
	}
	return (EXIT_SUCCESS);
}
