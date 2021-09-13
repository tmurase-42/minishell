/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:24:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/14 00:20:09 by tdofuku          ###   ########.fr       */
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
	if (token->next == NULL)
		return count;
	if (token->next->data != NULL
		&& ft_strncmp(token->next->data, "-n", 2) != 0)
		return (count);
	while (token)
	{
		if (token->data != NULL
			&& ft_strncmp(token->data, "-n", 2) == 0 && strchr_n(token->data))
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

static void	print_token_data(t_token *token)
{

	if (token->next != NULL)
		if (token->next->type == CHAR_DQUOTE
			|| token->next->type == CHAR_QUOTE)
			if (token->data[0] == '$' && ft_strlen(token->data) == 1)
				if (token->type == CHAR_GENERAL)
					return ;
	ft_putstr_fd(token->data, STDOUT_FILENO);
	if (token->next != NULL && token->next->space_len != 0)
		ft_putchar_fd(' ', STDOUT_FILENO);
}

int	ft_echo(t_cmd *cmd)
{
	int		option;
	t_token *tmp_token;

	tmp_token = cmd->args;
	if (cmd->argc < 2)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	option = option_check(tmp_token);
	tmp_token = delete_token(tmp_token, option);
	while (tmp_token)
	{
		print_token_data(tmp_token);
		tmp_token = tmp_token->next;
	}
	if (option == 1)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
