/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:26:17 by tmurase           #+#    #+#             */
/*   Updated: 2021/05/16 19:33:24 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_command	*command_init(t_env *envs)
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
	command_info->envs = envs;
	command_info->exit_status = 0;
	return (command_info);
}

int check_meta(char c)
{
	int	result;

	result = 0;
	if (c == ';')
		result = 1;
	if (c == '|')
		result = 1;
	if (c == '>')
		result = 1;
	if (c == '<')
		result = 1;

	return (result);
}
