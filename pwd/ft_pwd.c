/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:31:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/11 16:50:33 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd()
{
	char	pwd[PATH_MAX];
	extern t_mshl_data	*g_mshl_data;

	getcwd(pwd, PATH_MAX);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	g_mshl_data->exit_status = 0;
	return (g_mshl_data->exit_status);
}
