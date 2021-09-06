/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:05:32 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/06 15:58:33 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_redirect(t_redirect *redirect)
{
	if (redirect->type == CHAR_GREATER || redirect->type == DOUBLE_GREATER)
		redirect->backup_fd = dup(1);
	else
	{
		redirect->backup_fd = dup(0);
	}
	if (redirect->backup_fd < 0)
		ft_error_display("","",1);
	if (redirect->type == CHAR_GREATER || redirect->type == DOUBLE_GREATER)
	{
		if (dup2(redirect->right_fd, 1) < 0)
			ft_error_display("", "",1);
	}
	else
	{
		if (dup2(redirect->right_fd, 0) < 0)
			ft_error_display("", "",1);
	}
}
