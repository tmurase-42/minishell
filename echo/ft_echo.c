/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:24:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/23 15:21:03 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static t_bool option_check(t_token *token)
{
	if (ft_strncmp(token->next->data, "-n", 2) == 0)
		return (TRUE);
	return (FALSE);
}

static t_token *delete_token(t_token *token, int n)
{
	int	i;

	i = 0;
	while (token && i < n)
	{
		//なぜfreeできない？？？？？？？？？？？？？？？？？？？？？
		//free(token->data);
		token = token->next;
		i++;
	}
	return (token);
}
t_bool	ft_echo(t_cmd *cmd)
{
	int		option;

	option = 0;

	option = option_check(cmd->args);
	if (option == TRUE)
		cmd->args = delete_token(cmd->args, 2);
	else
		cmd->args = delete_token(cmd->args, 1);
	while (cmd->args)
	{
		ft_putstr_fd(cmd->args->data, 0);
		ft_putchar_fd(' ', 0);
		cmd->args = cmd->args->next;
	}
	if (option != TRUE)
		write(1, "\n", 1);
	return (TRUE);
}
