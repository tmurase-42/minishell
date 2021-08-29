/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:33:29 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/29 12:37:42 by tdofuku          ###   ########.fr       */
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

int			ft_env()
{
	extern t_mshl_data	*g_mshl_data;
	t_env			*current_env;

	current_env = g_mshl_data->envs;
	while (current_env)
	{
		print_env(current_env);
		current_env = current_env->next;
	}
	return (EXIT_SUCCESS);
}
