/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:17:42 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/03 12:35:16 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *message, int exit_status)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
	}
	exit(exit_status);
}

void	ft_error_display(char *command, char *name, int exit_status)
{
	extern t_mshl_data	*g_mshl_data;

	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
	g_mshl_data->exit_status = exit_status;
}

void	ft_free_char(char **target)
{
	free(*target);
	*target = NULL;
}

void    ft_safe_free_split(char ***target)
{
    size_t index;

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
