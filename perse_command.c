/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/23 08:31:31 by tmurase          ###   ########.fr       */
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
	int	exist_meta;

	num = 1;
	i = 0;
	exist_meta = 1;
	while (*command == SPACE)
		command++;
	while (*(command + i))
	{
		while (*(command + i) == SPACE && *(command + i + 1) == SPACE)
			i++;
		if (*(command + i) == ';')
		{	
			if (*(command + i + 1) == '\0')
				num++;
			else
				num+= 2;
		}
		if (*(command + i) == SPACE && *(command + i + 1) != '\0' && *(command + i - 1) != ';' && *(command + i + 1) != ';')
			num++;
		i++;
	}
	return (num);
}

static	char *split_command(char *command)
{
	size_t	len;
	size_t	exist_meta;
	char	*tmp;
	
	len = 0;
	exist_meta = 0;
	if (command[0] == ';')
	{
		exist_meta = 1;
		len++;
	}
	while (command[len] != 32 && command[len] != '\0' && !exist_meta)
	{	
		if (command[len] == ';')
			break;
		len++;
	}
	tmp = ft_substr(command , 0, len);
	return (tmp);
}

static int check_meta(char c)
{
	int	result;
		
	result = 0;
	if (c == ';')
		result = 1;
	
	return (result);
}


char	*shave_space(char *command, int index)
{
	int		i;
	size_t	exist_meta;
	char	*tmp;
	int		(* func)(char);

	func = check_meta;
	exist_meta = func(command[0]);
	i = 0;
	//if (command[0] == ';')
	printf("exist_meta = %zu\n", exist_meta);
	if (exist_meta == 1)
	{
		i++;
		while (command[i] == SPACE)
			i++;
		tmp = ft_strdup(command + i);
		free(command);
		return (tmp);
	}
	if (index != 0)
		while ((command[i] != SPACE && command[i] != ';') && command[i])
			i++;
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
