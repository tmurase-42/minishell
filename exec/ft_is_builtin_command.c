/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:36:17 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/19 19:54:16 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_is_builtin_command(t_token *token)
{
	const char	*commands[] = {"exit", "cd", "env", "unset",
		"export", "echo", "pwd", "<", "<<", ">", ">>", NULL};
	int			i;
	char		*str;

	i = 0;
	str = token->data;
	if (str == NULL)
		return (FALSE);
	while (commands[i])
	{
		if (ft_strncmp(str, commands[i], ft_strlen(commands[i])) == 0)
		{
			if (token->type == CHAR_GENERAL)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
