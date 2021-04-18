/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/16 08:51:10 by tmurase          ###   ########.fr       */
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
	while (*command == 32)
		command++;
	while (*(command + i))
	{
		if (!ft_strchr(command + i, 32))
			break;
		while (*(command + i) == 32 && *(command + i + 1) == 32)
			i++;
		if (*(command + i) == 32 && *(command + i + 1) != '\0')
			num++;
		i++;
	}
	return (num);
}

static	char *split_command(char *command)
{
	size_t	len;
	char	*tmp;
	
	len = 0;
	while (command[len] != 32 && command[len] != '\0')
		len++;
	tmp = ft_substr(command , 0, len);
	return (tmp);
}

void	strfree(char **str)
{
	int	i;
	
	i = 0;
	while (str)
	{
		while(str[i])
			free(str[i++]);
		free(str);
	}
}

char	*shave_space(char *command, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	if (index != 0)
		while (command[i] != 32 && command[i])
			i++;
	while (command[i] == 32 && command[i])
		i++;
	tmp = ft_strdup(command + i);
	free(command);
	return (tmp);
}
int	perse_command(char **command, t_command *command_info)
{
	int	index;
	int	i;
	
	//printf("command = %d\n", **command);
	//if (**command == '\0')
	//{
	//	printf("1111\n");
	//	return (0);
	//}
	//if (**command == 0)
	//{
	//	printf("2222\n");
	//	return (0);
	//}
	//if (command == NULL)
	//{
	//	printf("3333\n");
	//	return (0);
	//}
	command_info->argc = check_word_number(*command);
	command_info->argv = ft_calloc(command_info->argc + 1, sizeof(char *));
	if (!command_info->argv)
		return (1);
	index = 0;
	i = 0;
	while (command_info->argc > index)
	{	
		*command = shave_space(*command, index);
		command_info->argv[index] = split_command(*command);
		index++;
	}
	return (0);
}
