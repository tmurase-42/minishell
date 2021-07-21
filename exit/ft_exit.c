/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/03 13:50:30 by tdofuku          ###   ########.fr       */
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

t_bool ft_exit(t_command *command_info)
{
	if (ft_is_strdigit(command_info->argv[1]) == FALSE)
		ft_putstr_fd("引数が数字以外\n",2);
	if (command_info->argv[1] && command_info->argv[2])
		ft_putstr_fd("引数が複数\n", 2);
	ft_putstr_fd("exit\n", 2);
	return (TRUE);
}
