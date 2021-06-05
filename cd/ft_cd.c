/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:01:21 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/05 18:26:16 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool ft_cd(t_command *command_info)
{
	t_env	*dir;
	int		result;

	dir = ft_env_get("HOME",command_info->envs);
	printf("dir->value = %s\n", dir->value);
	result = chdir(dir->value);
	printf("dir->value = %s\n", dir->value);
	ft_env_update("PWD", dir->value, command_info->envs);
	ft_env_update("OLDPWD", dir->value, command_info->envs);
	return TRUE;
}
