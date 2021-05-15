/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 19:38:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/15 17:29:47 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_bool	is_identifier(char *name)
{
	size_t	i;

	i = 0;
	if (name[i] != '_' && !ft_isalpha(name[i]))
		return (FALSE);
	i++;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int				ft_unset(t_command *command_info)
{
	size_t	i;
	int		ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (command_info->argv[i])
	{
		if (is_identifier(command_info->argv[i]) == TRUE)
		{
			ft_env_delete(command_info->argv[i], command_info->envs);
		}
		else
		{
			// -bash: unset: `.jfe': not a valid identifier
			// ↑こんな感じの文字列をはかせる
			ret = EXIT_FAILURE;
		}
		i++;
	}
	return (ret);
}
