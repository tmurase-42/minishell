/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:16 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/14 23:03:39 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_bool	check_error_open_close(t_redirect *redir, int final_fd)
{
	if (redir->right_fd < 0)
		return (FALSE);
	if (redir->right_fd != final_fd)
		if (close(redir->right_fd) < 0)
			return (FALSE);
	return (TRUE);
}

t_bool	ft_check_redirect(t_cmd *cmd)
{
	t_redirect	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == CHAR_GENERAL || redir->type == DOUBLE_GREATER)
			if (check_error_open_close(redir, cmd->final_greater_fd) == FALSE)
				return (FALSE);
		if (redir->type == DOUBLE_LESSER)
			if (check_error_open_close(redir, cmd->final_lesser_fd) == FALSE)
				return (FALSE);
		redir = redir->next;
	}
	return (TRUE);
}
