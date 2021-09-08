/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:34:08 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/08 16:21:35 by tdofuku          ###   ########.fr       */
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
	return (EXIT_FAILURE);
}
