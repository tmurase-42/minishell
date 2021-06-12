/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/06/12 15:06:16 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp_command(char *str, int len)
{
	int tmp;

	tmp = len;
	if (ft_strncmp(str, "exit", 4) == 0)
		len += 4;
	if (ft_strncmp(str, "cd", 2) == 0)
		len += 2;
	if (ft_strncmp(str, "pwd", 3) == 0)
		len += 3;
	if (ft_strncmp(str, "export", 6) == 0)
		len += 6;
	if (ft_strncmp(str, "unset", 5) == 0)
		len += 5;
	if (ft_strncmp(str, "env", 3) == 0)
		len += 3;
	if (ft_strncmp(str, "echo", 4) == 0)
		len += 4;
	return (len);
}

static int	check_word_number(char *command)
{
	int	word_num;
	int	len;

	word_num = 0;
	len = 0;
	while (command[len])
	{
		if ((command[len - 1] == SPACE && command[len] != SPACE) && command[len] != '\0')
			word_num++;
		len = cmp_command(command + len , len);
		if (command[len] == DOUBLE_QUOT)
		{
			len++;
			while (command[len] != DOUBLE_QUOT)
				len++;
		}
		if(command[len] == SINGLE_QUOT)
		{
			len++;
			while (command[len] != SINGLE_QUOT)
				len++;
		}
		len++;
	}
	if (command[len] == '\0')
		word_num++;
	return (word_num);
}

static int	cmp_command_tmp(char *str, int len)
{
	if (ft_strncmp(str, "exit", 4) == 0)
		len += 4;
	if (ft_strncmp(str, "cd", 2) == 0)
		len += 2;
	if (ft_strncmp(str, "pwd", 3) == 0)
		len += 3;
	if (ft_strncmp(str, "export", 6) == 0)
		len += 6;
	if (ft_strncmp(str, "unset", 5) == 0)
		len += 5;
	if (ft_strncmp(str, "env", 3) == 0)
		len += 3;
	if (ft_strncmp(str, "echo", 4) == 0)
		len += 4;
	return (len);
}

static	void	split_word(char *command, t_command *command_info)
{
	int	index;
	int	len;
	int tmp;
	t_mode	mode;

	mode.NEUTRAL = TRUE;
	mode.SINGLE = FALSE;
	mode.DOUBLE = FALSE;
	index = 0;
	len = 0;
	while (command_info->argc > index)
	{
		tmp = 0;
		while (command[len] == SPACE)
			len++;
		tmp = cmp_command_tmp(command+len, len);
		if (tmp > len && (command[tmp] == SPACE || command[tmp] == '\0'))
		{
			command_info->argv[index] = ft_substr(command + len, 0, tmp - len);
			len = tmp;
		}
		else
		{
			tmp = 0;
			while (command[len + tmp] != '\0')
			{
				if (check_meta(command[len]) == TRUE)
				{
					if (command[len  + 1] == '>')
						tmp++;
					tmp++;
					break;
				}
				if (command[len + tmp] == SINGLE_QUOT)
				{
					mode.NEUTRAL = FALSE;
					tmp++;
					while (command[len + tmp] != SINGLE_QUOT)
						tmp++;
				}
				mode.NEUTRAL = TRUE;
				if (command[len + tmp] == DOUBLE_QUOT)
				{
					mode.NEUTRAL = FALSE;
					tmp++;
					while(command[len + tmp] != DOUBLE_QUOT)
						tmp++;
				}
				mode.NEUTRAL = TRUE;
				if (check_meta(command[len + tmp]) == TRUE && mode.NEUTRAL == TRUE)
				{
					break;
				}
				if (command[len + tmp - 1] != SPACE && command[len + tmp] == SPACE)
					break;
				tmp++;
			}
			command_info->argv[index] = ft_substr(command, len, tmp);
			len += tmp;
		}
		index++;
	}
}

int	ft_lexer(char **command, t_command *command_info)
{
	command_info->argc = check_word_number(*command);
	command_info->argv = ft_calloc(command_info->argc + 1, sizeof(char *));
	if (!command_info->argv)
		return (1);
	split_word(*command, command_info);
	return (0);
}
