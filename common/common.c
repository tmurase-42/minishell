/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:17:42 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/26 21:24:12 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *message, char *command, int status_num)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(status_num);
}

void	ft_error_identifier(char *command, char *name)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("", STDERR_FILENO);
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
