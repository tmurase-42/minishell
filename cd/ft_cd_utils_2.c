/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:52:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/07 16:19:59 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_is_tilde(t_cmd *cmd)
{
	t_token	*tmp;

	if (cmd->argc < 2)
		return (FALSE);
	tmp = cmd->args->next;
	if (ft_strncmp("~", tmp->data, 1) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	ft_isnot_path(t_mshl_data *g_mshl_data, char *pwd)
{
	t_env	*dir;

	dir = ft_env_get("HOME", g_mshl_data->envs);
	if (!dir)
		ft_error_display("minishell", "ft_env_get: unexpected error", 1);
	ft_env_update("PWD", dir->value);
	ft_env_update("OLDPWD", pwd);
	if (chdir(dir->value) != 0)
		ft_error_display("minishell", "chdir: unexpected error", 1);
	else
	{
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ft_error_cd(char *file)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (FALSE);
}
