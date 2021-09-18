/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:17:42 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 22:20:45 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *command, char *message, int exit_status)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	if (command != NULL && *command != '\0')
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
		free(command);
	}
	if (errno != 0)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	else if (message != NULL && *message != '\0')
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		free(message);
	}
	else
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("Undefined error occured.", STDERR_FILENO);
	}
	ft_putendl_fd("", STDERR_FILENO);
	ft_mshl_data_destroy();
	exit(exit_status);
}

void	ft_error_display(char *command, char *message, int exit_status)
{
	extern t_mshl_data	*g_mshl_data;

	ft_putstr_fd("minishell", STDERR_FILENO);
	if (command != NULL && *command != '\0')
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
	}
	if (message != NULL && *message != '\0')
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("Undefined error occured.", STDERR_FILENO);
	}
	ft_putendl_fd("", STDERR_FILENO);
	g_mshl_data->exit_status = exit_status;
}

void	ft_free_char(char **target)
{
	free(*target);
	*target = NULL;
}

void	ft_safe_free_split(char ***target)
{
	size_t	index;

	index = 0;
	if (!*target)
		return ;
	while ((*target)[index])
	{
		free((*target)[index]);
		(*target)[index] = NULL;
		index++;
	}
	free(*target);
	*target = NULL;
}
