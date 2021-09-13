/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/13 20:54:23 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_is_strdigit(char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (ft_isdigit(str[index]) == TRUE)
			index++;
		else if (str[index] == '-' && count == 0)
		{
			index++;
			count++;
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	check_args(t_cmd *cmd)
{
	t_token	*token_next;

	token_next = cmd->args->next;
	if (ft_is_strdigit(token_next->data) == TRUE && ft_is_strdigit(token_next->next->data) == TRUE)
		return (FALSE);
	if (ft_strcmp(token_next->data, "--") != 0 && ft_atoi(token_next->data) == 0)
		ft_error_num(cmd);
	if (ft_strcmp(token_next->data, "--") == 0)
		ft_token_destroy(token_next, &cmd->args);
	else if (ft_is_strdigit(token_next->data) == FALSE)
		ft_error_num(cmd);
	if (ft_strcmp(token_next->data, "--") == 0)
		ft_error_num(cmd);
	if (cmd->argc > 3)
		return (FALSE);
	return (TRUE);
}

int	ft_exit(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (cmd->argc > 2)
	{
		if (check_args(cmd) == FALSE)
		{
			ft_putstr_fd("exit\n", 2);
			return (ft_error_exit("too many arguments"));
		}
	}
	if (cmd->argc > 1)
	{
		if (ft_atoi(cmd->args->next->data) != 0 )
			cmd->args->next->data = ft_strtrim(cmd->args->next->data, " ");
		if ((ft_is_strdigit(cmd->args->next->data) == FALSE) || ft_strcmp(cmd->args->next->data, "-") == 0)
			ft_error_num(cmd);
		status = ft_atoi(cmd->args->next->data);
	}
	ft_putstr_fd("exit\n", 2);
	if (cmd->argc < 2)
		exit(EXIT_SUCCESS);
	else
		exit(status);
}
