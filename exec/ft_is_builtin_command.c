/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:36:17 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/12 20:28:41 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_is_builtin_command(char *str)
{
	const char *commands[] = {"exit", "cd", "env", "unset", "export", "echo", "pwd", "<", "<<", ">", ">>", NULL};
	int		i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (commands[i])
	{
		if (ft_strncmp(str, commands[i], ft_strlen(commands[i])) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
