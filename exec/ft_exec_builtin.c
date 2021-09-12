/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:34:08 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/12 20:38:47 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args->data, "echo", ft_strlen(cmd->args->data)) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->args->data, "exit", ft_strlen(cmd->args->data)) == 0)
		return (ft_exit(cmd));
	if (ft_strncmp(cmd->args->data, "env", ft_strlen(cmd->args->data)) == 0)
		return (ft_env());
	if (ft_strncmp(cmd->args->data, "export", ft_strlen(cmd->args->data)) == 0)
		return (ft_export(cmd));
	if (ft_strncmp(cmd->args->data, "unset", ft_strlen(cmd->args->data)) == 0)
		return (ft_unset(cmd));
	if (ft_strncmp(cmd->args->data, "pwd", ft_strlen(cmd->args->data)) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd->args->data, "cd", ft_strlen(cmd->args->data)) == 0)
		return (ft_cd(cmd));
	if (ft_strncmp(cmd->args->data, ">", ft_strlen(cmd->args->data)) == 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(cmd->args->data, "<", ft_strlen(cmd->args->data)) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
