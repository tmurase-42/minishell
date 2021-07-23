/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:24:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/23 15:55:27 by tmurase          ###   ########.fr       */
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
	t_token *tmp_token;

	option = 0;
	tmp_token = cmd->args;
	option = option_check(tmp_token);
	if (option == TRUE)
		tmp_token = delete_token(tmp_token, 2);
	else
		tmp_token = delete_token(tmp_token, 1);
	while (tmp_token)
	{
		ft_putstr_fd(tmp_token->data, 0);
		if (tmp_token->next != NULL)
			ft_putchar_fd(' ', 0);
		tmp_token = tmp_token->next;
	}
	if (option != TRUE)
		write(1, "\n", 1);
	return (TRUE);
}
