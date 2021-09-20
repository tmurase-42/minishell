/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:05:32 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/20 13:58:03 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*select_redir(t_redir *redir, t_redir *tmp)
{
	while (tmp)
	{
		if (redir->left_fd == tmp->left_fd && redir->l_type == tmp->l_type)
		{
			redir = redir->next;
			tmp = tmp->next;
			continue ;
		}
		tmp = tmp->next;
	}
	return (redir);
}

t_bool	select_dup(t_redir *redir, int is_parent)
{
	t_redir	*tmp;

	tmp = redir->next;
	while (redir)
	{
		redir = select_redir(redir, tmp);
		tmp = NULL;
		if (is_parent == TRUE)
		{
			redir->backup_fd = dup(redir->left_fd);
			if (redir->backup_fd < 0)
				return (FALSE);
		}
		if (dup2(redir->right_fd, redir->left_fd) < 0)
			return (FALSE);
		close(redir->right_fd);
		redir = redir->next;
		if (redir == NULL)
			break ;
		if (redir->next != NULL)
			tmp = redir->next;
	}
	return (TRUE);
}

t_bool	ft_dup_redirect(t_cmd *cmd, int	is_parent)
{
	t_redir	*greater_redir;
	t_redir	*lesser_redir;

	greater_redir = cmd->redirect;
	lesser_redir = cmd->redirect;
	if (cmd->final_greater_fd < 0 && cmd->final_lesser_fd < 0)
		return (TRUE);
	if (select_dup(greater_redir, is_parent) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	select_backup(t_redir *redir)
{
	while (redir)
	{
		if (redir->backup_fd > -1)
		{
			if (dup2(redir->backup_fd, redir->left_fd) < 0)
				return (FALSE);
		}
		redir = redir->next;
	}
	return (TRUE);
}

t_bool	ft_backup_fd(t_cmd *cmd)
{
	t_redir	*greater_redir;
	t_redir	*lesser_redir;

	greater_redir = cmd->redirect;
	lesser_redir = cmd->redirect;
	if (select_backup(greater_redir) == FALSE)
		return (FALSE);
	return (TRUE);
}
