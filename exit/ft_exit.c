/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/08/26 19:35:18 by tdofuku          ###   ########.fr       */
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
		ft_error("exit", "too many arguments.", 1);
	if (cmd->argc == 2 && ft_is_strdigit(cmd->args->next->data) == FALSE)
		ft_error("exit", "numeric number is required.", 1);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}
