/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/13 20:47:35 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_error_exit(char *massage)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(massage, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_error_num(t_cmd *cmd)
{
	char	*str;

	str = cmd->args->next->data;
	ft_putstr_fd("exit\n", 2);
	ft_error("exit", ft_strjoin(str, ": numeric argument required"), 255);
}
