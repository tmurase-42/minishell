/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:05:32 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 03:04:16 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	select_dup2(t_redir *redir, int num, int final_fd, int is_parent)
{
	if (final_fd != 0)
	{
		while (redir)
		{
			if (redir->right_fd == final_fd)
				break ;
			redir = redir->next;
		}
		if (is_parent == TRUE)
		{
			redir->backup_fd = dup(num);
			if (redir->backup_fd < 0)
				return (FALSE);
		}
		if (dup2(final_fd, redir->left_fd) < 0)
			return (FALSE);
		close(final_fd);
	}
	return (TRUE);
}

t_bool	ft_dup_redirect(t_cmd *cmd, int	is_parent)
{
	t_redir	*greater_redir;
	t_redir	*lesser_redir;

	greater_redir = cmd->redirect;
	lesser_redir = cmd->redirect;
	if (select_dup2(greater_redir, 1,
			cmd->final_greater_fd, is_parent) == FALSE)
		return (FALSE);
	if (select_dup2(lesser_redir, 0, cmd->final_lesser_fd, is_parent) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	select_backup(t_redir *redir, int fd, int final_fd)
{
	if (final_fd != 0)
	{
		while (redir)
		{
			if (redir->right_fd == final_fd)
				break ;
			redir = redir->next;
		}
		if (dup2(redir->backup_fd, fd) < 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	ft_backup_fd(t_cmd *cmd)
{
	t_redir	*greater_redir;
	t_redir	*lesser_redir;

	greater_redir = cmd->redirect;
	lesser_redir = cmd->redirect;
	if (select_backup(greater_redir, 1, cmd->final_greater_fd) == FALSE)
		return (FALSE);
	if (select_backup(lesser_redir, 0, cmd->final_lesser_fd) == FALSE)
		return (FALSE);
	return (TRUE);
}
