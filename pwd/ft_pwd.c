/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:31:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/06 16:38:17 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool ft_pwd(t_command *command_info)
{
	char	pwd[PATH_MAX];
	
	(void)command_info;
	getcwd(pwd, PATH_MAX);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (TRUE);
}
