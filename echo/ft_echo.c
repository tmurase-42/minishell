/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:24:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/12 21:16:45 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool strchr_n(char *str)
{
	int i;

	i = 0;
	str += 2;
	if (str == NULL)
		return (TRUE);
	while(str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

static int option_check(t_token *token)
{
	int count;

	count = 1;
	if (ft_strncmp(token->next->data, "-n", 2) != 0)
		return (count);
	while (token)
	{
		if (ft_strncmp(token->data, "-n", 2) == 0 && strchr_n(token->data))
			count++;
		token = token->next;
	}
	return (count);
}

static t_token *delete_token(t_token *token, int n)
{
	int	i;
	i = 0;
	if (n == 0)
		return (token->next);
	while (token && i < n)
	{
		token = token->next;
		i++;
	}
	return (token);
}

int	ft_echo(t_cmd *cmd)
{
	int		option;
	t_token *tmp_token;
	extern t_mshl_data	*g_mshl_data;

	tmp_token = cmd->args;
	if (cmd->argc < 2)
		return (g_mshl_data->exit_status);
	option = option_check(tmp_token);
	tmp_token = delete_token(tmp_token, option);
	while (tmp_token)
	{
		ft_putstr_fd(tmp_token->data, STDOUT_FILENO);
		if (tmp_token->next != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		tmp_token = tmp_token->next;
	}
	if (option == 1)
		write(1, "\n", 1);
	return (g_mshl_data->exit_status);
}
