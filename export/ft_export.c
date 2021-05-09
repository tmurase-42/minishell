/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:50:48 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/07 19:55:09 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_export(char **args, t_env *envs)
{
	int	i;
	i = (int)args * (int)envs;
	// if (args[1])
	// {
	// 	return (set_envs(args));
	// }
	// else
	// {
	// 	return (print_envs());
	// }
	return (EXIT_SUCCESS);
}
