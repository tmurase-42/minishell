/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:01:21 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/23 13:31:38 by tdofuku          ###   ########.fr       */
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

t_bool ft_cd(t_cmd *cmd, t_mshl_data *mshl_data)
{
	t_env	*dir;
	char	pwd[PATH_MAX];
	char	*parent_dir;
	int		result;

	getcwd(pwd, PATH_MAX);
	printf("pwd = %s\n", pwd);
	if (cmd->argc < 2)
	{
		dir = ft_env_get("HOME", mshl_data->envs);
		ft_env_update("PWD", dir->value, mshl_data->envs);
		ft_env_update("OLDPWD", pwd, mshl_data->envs);
		result = chdir(dir->value);
	}
	else if (ft_strncmp(cmd->args->next->data, "..", 2) == 0)
	{
		parent_dir = get_parentdirectory(pwd);
		printf("parent_dir = %s\n", parent_dir);
		ft_env_update("PWD", parent_dir, mshl_data->envs);
		ft_env_update("OLDPWD", pwd, mshl_data->envs);
		result = chdir(parent_dir);
	}
	else if (ft_strncmp(cmd->args->next->data, ".", 1) == 0)
	{
		ft_env_update("OLDPWD", pwd, mshl_data->envs);
		result = chdir(pwd);
	}
	else
	{
		ft_env_update("PWD", cmd->args->next->data, mshl_data->envs);
		ft_env_update("OLDPWD", pwd, mshl_data->envs);
		result = chdir(cmd->args->next->data);
	}
	getcwd(pwd, PATH_MAX);
	printf("pwd = %s\n", pwd);
	if (result != 0)
		return (FALSE);
	return (TRUE);
}
