/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:01:21 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/06 13:34:55 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool ft_cd(t_command *command_info)
{
	t_env	*dir;
	char	pwd[PATH_MAX];
	int		result;

	getcwd(pwd, PATH_MAX);
	if (command_info->argc < 2)
	{
		dir = ft_env_get("HOME", command_info->envs);
		ft_env_update("PWD", dir->value, command_info->envs);
		ft_env_update("OLDPWD", pwd, command_info->envs);
		result = chdir(dir->value);
	}
	return TRUE;
}
