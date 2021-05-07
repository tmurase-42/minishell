/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:17:42 by tdofuku           #+#    #+#             */
/*   Updated: 2021/05/07 16:48:48 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_error(char *str)
{
	ft_putstr_fd("エラーを吐く\n", 1);
	return 0 * (int)str;
}

void	ft_free_char(char **target)
{
	free(*target);
	*target = NULL;
}
