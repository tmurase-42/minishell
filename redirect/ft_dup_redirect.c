/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:05:32 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/20 10:57:50 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	select_dup(t_redir *redir, int is_parent)
{
	t_redir	*tmp;

	tmp = redir->next;
	while (redir)
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
		if (is_parent == TRUE)
		{
			redir->backup_fd = dup(redir->left_fd);
			if (redir->backup_fd < 0)
				return (FALSE);
		}
	//	printf("bakcup_fd:[%d]\n", redir->backup_fd);
	//	printf("left_fd:[%d]\n", redir->left_fd);
	//	printf("right_fd:[%d]\n", redir->right_fd);
	//	printf("left_fd:[%d]\n", redir->left_fd);
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
	//ft_test_print_redirect(cmd);
	if (select_dup(greater_redir, is_parent) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool	select_backup(t_redir *redir)
{
	while(redir)
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
