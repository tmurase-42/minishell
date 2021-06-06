/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:01:21 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/06 12:15:11 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool ft_cd(t_command *command_info)
{
	t_env	*dir;
	int		result;
	if (command_info->argc > 2)
	{
		dir = ft_env_get("HOME", command_info->envs)
		
	}
	dir = ft_env_get("HOME",command_info->envs);
	printf("dir->value = %s\n", dir->value);
	result = chdir(dir->value);
	printf("dir->value = %s\n", dir->value);
	ft_env_update("PWD", dir->value, command_info->envs);
	ft_env_update("OLDPWD", "/user/bin", command_info->envs);
	return TRUE;
}
