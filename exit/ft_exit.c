/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/03 12:35:36 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	ft_is_strdigit(char *str)
{
	int	index;

	index = 0;
	while (str[index] == CHAR_WHITESPACE)
		index++;
	while (str[index])
	{
		if (ft_isdigit(str[index]) == TRUE)
			index++;
		else
			return (FALSE);
	}
	return (TRUE);
}

t_bool	ft_error_exit(char *massage)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(massage, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int ft_exit(t_cmd *cmd)
{
	if (cmd->argc > 2)
	{
		ft_putstr_fd("logout\n", 2);
		return (ft_error_exit("too many arguments"));
	}
	if (cmd->argc == 2 && ft_is_strdigit(cmd->args->next->data) == FALSE)
	{
		ft_error("numeric number is required", 255);
	}
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}
