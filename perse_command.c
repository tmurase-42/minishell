/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/28 14:48:18 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotation(char *command, int i)
{
	if (*(command + i) == '"')
	{
		i++;
		while (*(command + i) != '"')
		{
			i++;
		if (*(command + i) == '"')
			return (i);
		}
	}
	if (*(command + i) == 39)
	{
		i++;
		while (*(command + i) != 39)
		{
			i++;
		if (*(command + i) == 39)
			return (i);
		}
	}
	return (i);
}

static int	check_word_number(char *command)
{
	int	num;
	int	i;
	int	(* func)(char);

	num = 0;
	i = 0;
	func = check_meta;
	while (*command == SPACE)
		command++;
	while (*(command + i))
	{
		while (*(command + i) == SPACE && *(command + i + 1) == SPACE)
			i++;
		i = check_quotation(command, i);
		if (func(*(command + i)) == TURE)
		{	
			if (*(command + i + 1) == '\0')
				num++;
			else
				num+= 2;
		}
		if (*(command + i) == SPACE && *(command + i + 1) != '\0' &&
			func(*(command + i - 1)) == FALSE && func(*(command + i + 1)) == FALSE)
			num++;
		i++;
		if (*(command + i) == '\0')
			num++;
	}
	return (num);
}

static int	check_length_quotation(char *command, char quotation, int len)
{
	len++;
	while (command[len])
	{
		if (command[len] == quotation)
			return (len + 1);
		len++;
	}
	return (len);
}

static	char *split_command(char *command)
{
	int		len;
	char	*tmp;
	
	len = 0;
	if (check_meta(command[0]) == TURE)
		len++;
	while (command[len] != SPACE && command[len] != '\0' && check_meta(command[0]) == FALSE)
	{	
		if (command[len] == DOUBLE_QUO || command[len] == SINGLE_QUO)
		{
			len = check_length_quotation(command, command[len], len);
			break;
		}
		if (check_meta(command[len]) == TURE)
			break;
		len++;
	}
	tmp = ft_substr(command , 0, len);
	return (tmp);
}

char	*shave_space(char *command, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	if (check_meta(command[0]) == TURE && index > 0)
	{
		i++;
		while (command[i] == SPACE)
			i++;
		tmp = ft_strdup(command + i);
		free(command);
		return (tmp);
	}
	if (index != 0)
		while ((command[i] != SPACE && check_meta(command[i]) == FALSE) && command[i])
		{	
			if (command[i] == DOUBLE_QUO || command[i] == SINGLE_QUO)
			{
				i = check_length_quotation(command, command[i], i);
				break;
			}
			i++;
		}
	while ((command[i] == SPACE) && command[i])
		i++;
	tmp = ft_strdup(command + i);
	free(command);
	return (tmp);
}

int	perse_command(char **command, t_command *command_info)
{
	int	index;
	int	i;
	
	command_info->argc = check_word_number(*command);
	command_info->argv = ft_calloc(command_info->argc + 1, sizeof(char *));
	if (!command_info->argv)
		return (1);
	index = 0;
	i = 0;
	while (command_info->argc > index)
	{	
		*command = shave_space(*command, index);
		printf("command = %s\n", *command);
		command_info->argv[index] = split_command(*command);
		index++;
		i++;
	}
	return (0);
}
