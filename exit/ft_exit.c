/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/12 17:01:52 by tmurase          ###   ########.fr       */
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

t_bool	ft_error_exit(char *massage)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(massage, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
static void ft_error_num(t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 2);
	ft_error("exit", ft_strjoin(cmd->args->next->data, ": numeric argument required"), 255);
}

static t_bool check_args(t_cmd *cmd)
{

	if (ft_is_strdigit(cmd->args->next->data) == TRUE && ft_is_strdigit(cmd->args->next->next->data) == TRUE)
		return (FALSE);
	if (ft_strcmp(cmd->args->next->data, "--") != 0 && ft_atoi(cmd->args->next->data) == 0)
		ft_error_num(cmd);
	if (ft_strcmp(cmd->args->next->data, "--") == 0)
		ft_token_destroy(cmd->args->next, &cmd->args);
	else if (ft_is_strdigit(cmd->args->next->data) == FALSE)
	{
		ft_error_num(cmd);
	}
	if (ft_strcmp(cmd->args->next->data, "--") == 0)
	{
		ft_error_num(cmd);
	}
	if (cmd->argc > 3)
		return (FALSE);
	return (TRUE);
}

int ft_exit(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (cmd->argc > 2)
		if (check_args(cmd) == FALSE)
		{
			ft_putstr_fd("exit\n", 2);
			return (ft_error_exit("too many arguments"));
		}
	if (cmd->argc > 1)
	{
		status = ft_atoi(cmd->args->next->data);
		//if ((ft_is_strdigit(cmd->args->next->data) == FALSE))
		//{
			//ft_error_num(cmd);
		//}
		//printf("saaa\n");
		if ((ft_is_strdigit(cmd->args->next->data) == FALSE && status == 0) || ft_strcmp(cmd->args->next->data, "-") == 0)
		{
			//printf("dfsafasfdasf\n");
			ft_error_num(cmd);
		}
	}
	ft_putstr_fd("exit\n", 2);
	if (cmd->argc < 2)
		exit(EXIT_SUCCESS);
	else
		exit(status);
}
