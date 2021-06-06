/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:01:21 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/06 16:22:25 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char *get_parentdirectory(char *str)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(str);
	tmp = NULL;
	while (len != 0)
	{
		if (str[len] == '/')
		{
			tmp = ft_substr(str, 0, len);
			break ;
		}
		len--;
		printf("count\n");
	}
	printf("tmp = %s\n", tmp);
	return (tmp);
}

t_bool ft_cd(t_command *command_info)
{
	t_env	*dir;
	char	pwd[PATH_MAX];
	char	*parent_dir;
	int		result;

	getcwd(pwd, PATH_MAX);
	printf("pwd = %s\n", pwd);
	if (command_info->argc < 2)
	{
		dir = ft_env_get("HOME", command_info->envs);
		ft_env_update("PWD", dir->value, command_info->envs);
		ft_env_update("OLDPWD", pwd, command_info->envs);
		result = chdir(dir->value);
	}
	else if (ft_strncmp(command_info->argv[1], "..", 2) == 0)
	{
		parent_dir = get_parentdirectory(pwd);
		printf("parent_dir = %s\n", parent_dir);
		ft_env_update("PWD", parent_dir, command_info->envs);
		ft_env_update("OLDPWD", pwd, command_info->envs);
		result = chdir(parent_dir);
	}
	else if (ft_strncmp(command_info->argv[1], ".", 1) == 0)
	{
		ft_env_update("OLDPWD", pwd, command_info->envs);
		result = chdir(pwd);
	}
	else
	{
		ft_env_update("PWD", command_info->argv[1], command_info->envs);
		ft_env_update("OLDPWD", pwd, command_info->envs);
		result = chdir(command_info->argv[1]);
	}
	getcwd(pwd, PATH_MAX);
	printf("pwd = %s\n", pwd);
	if (result != 0)
		return (FALSE);
	return (TRUE);
}
