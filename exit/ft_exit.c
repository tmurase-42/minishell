/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/23 13:13:17 by tdofuku          ###   ########.fr       */
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

t_bool ft_exit(t_cmd *cmd)
{
	if (cmd->argc > 2)
		ft_error("error", "exitの引数が複数になっています。");
	if (cmd->argc == 2 && ft_is_strdigit(cmd->args->next->data) == FALSE)
		ft_error("error", "exitの引数が数字以外になっています。");
	ft_putstr_fd("exit\n", 2);
	return (TRUE);
}
