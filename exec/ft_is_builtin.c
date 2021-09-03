/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:36:17 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 22:44:10 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	is_builin_command(char *str)
{
	const char *commands[] = {"exit", "cd", "env", "unset", "export", "echo", "pwd", "history", NULL};
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