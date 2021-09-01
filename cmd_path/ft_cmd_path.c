/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 20:51:39 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 17:16:20 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_type	judge_cmd_type(const char *str)
{
	if (*str == '/')
		return (ABSOLUTE);
	else if (ft_strchr(str, '/') != NULL)
		return (RELATIVE);
	else
		return (COMMAND);
}

static void	check_cmd_path(const char *cmd, const char *path)
{
	if (path == NULL)
	{
		ft_error_display("command not found", (char *)cmd, EXIT_FAILURE);
		exit(STATUS_CMD_NOT_FOUND);
	}
}

char	*ft_cmd_path(const char *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	t_cmd_type			type;
	char				*res;

	if (!cmd)
		return (NULL);
	type = judge_cmd_type(cmd);
	if (type == COMMAND)
		res = ft_cmd_path_search_binary(cmd);
	else
	{
		res = ft_strdup(cmd);
		if (!res)
			ft_error(NULL, NULL, 1);
	}
	check_cmd_path(cmd, res);
	return (res);
}
