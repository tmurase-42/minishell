/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/20 13:14:55 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	is_strdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(ft_isdigit(str[i]) || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
			|| str[i] == ' ' || str[i] == '+' || str[i] == '-')
		{
			i++;
		}
		else
		{
			return (FALSE);
		}
	}
	if (ft_atoi(str) != 0 || (str[0] == '0' && str[1] == '\0'))
		return (TRUE);
	return (FALSE);
}

static void	get_exit_status(t_cmd *cmd, char **message, t_bool *exit_flag)
{
	extern t_mshl_data	*g_mshl_data;
	char	*first_args;

	if (cmd->args->next)
		first_args = cmd->args->next->data;
	else
		first_args = NULL;
	if (cmd->argc == 3 && ft_strncmp(first_args, "--", ft_strlen(first_args)) == 0 && cmd->args->next->next && is_strdigit(cmd->args->next->next->data))
		g_mshl_data->exit_status = ft_atoi(cmd->args->next->next->data);
	else if (cmd->argc >= 2 && is_strdigit(first_args) == FALSE)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		*message = ft_strjoin(first_args, ": numeric argument required");
		g_mshl_data->exit_status = 255;
	}
	else if (cmd->argc > 2 && is_strdigit(first_args) == TRUE)
	{
		*message = "minishell: exit: too many arguments";
		g_mshl_data->exit_status = EXIT_FAILURE;
		*exit_flag = FALSE;
	}
	else if (cmd->argc == 2 && is_strdigit(first_args) == TRUE)
		g_mshl_data->exit_status = ft_atoi(cmd->args->next->data);
	else
		g_mshl_data->exit_status = EXIT_SUCCESS;
}

int	ft_exit(t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char	*message;
	t_bool	exit_flag;

	message = NULL;
	exit_flag = TRUE;

	get_exit_status(cmd, &message, &exit_flag);

	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	else
		ft_putendl_fd("exit", STDERR_FILENO);

	if (exit_flag == TRUE)
		exit(g_mshl_data->exit_status);
	return (g_mshl_data->exit_status);
}
