/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/01 23:03:26 by tdofuku          ###   ########.fr       */
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

int ft_exit(t_cmd *cmd)
{
	if (cmd->argc > 2)
		ft_error("too many arguments.", EXIT_FAILURE);
	if (cmd->argc == 2 && ft_is_strdigit(cmd->args->next->data) == FALSE)
		ft_error("a numeric argument is required.", EXIT_FAILURE);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}
