/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/11 09:37:56 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_command	*command_init(void)
{
	t_command	*command_info;
	command_info = malloc(sizeof(t_command));
	if (!command_info)
		return (NULL);
	command_info->next = NULL;
	command_info->argc = 0;
	command_info->argv = NULL;
	command_info->op = 0;
	command_info->pid = -1;
	
	return (command_info);
}

static int	check_word_number(char *command)
{
	int	num;
	int	i;

	num = 1;
	i = 0;
	while (*(command + i))
	{
		if (*(command + i) == 32)
		{
			while (*(command + i) != 32)
				i++;
			if (*(command + i + 1) != 32 && *(command + i + 1) != '\0')
				num++;
		}
		else if (!ft_strchr(command, 32))
			num = 1;
		i++;
	}
	return (num);
}

int		perse_command(char **command, t_command *command_info)
{
	(void)command;
	command_info->argc = check_word_number(*command);
	
	return (1);
}
