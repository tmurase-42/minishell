/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:05:32 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/10 10:53:05 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_dup_redirect(t_cmd *cmd, int	is_parent)
{
	t_redirect	*greater_redir;
	t_redirect	*lesser_redir;

	greater_redir = cmd->redirect;
	lesser_redir = cmd->redirect;
	if (cmd->final_greater_fd != 0)
	{
		while(greater_redir)
		{
			if (greater_redir->right_fd == cmd->final_greater_fd)
				break;
			greater_redir = greater_redir->next;
		}
		if (is_parent == TRUE)
		{
			greater_redir->backup_fd = dup(1);
			if (greater_redir->backup_fd < 0)
			{
				ft_error_display("minishell", "dup2", 1);
				return (FALSE);
			}
		}
		if (dup2(cmd->final_greater_fd, greater_redir->left_fd) < 0)
		{
			ft_error_display("minishell", "dup2", 1);
			return (FALSE);
		}
		close(cmd->final_greater_fd);
	}
	if (cmd->final_lesser_fd != 0)
	{
		while(lesser_redir)
		{
			if (lesser_redir->right_fd == cmd->final_lesser_fd)
				break ;
			lesser_redir = lesser_redir->next;
		}
		if (is_parent == TRUE)
		{
			lesser_redir->backup_fd = dup(0);
			if (lesser_redir->backup_fd < 0)
			{
				ft_error_display("minishell", "dup", 1);
				return (FALSE);
			}
		}
		if (dup2(cmd->final_lesser_fd, lesser_redir->left_fd) < 0)
		{
			ft_error_display("minishell", "dup2", 1);
			return (FALSE);
		}
		close(cmd->final_lesser_fd);
	}
	//ft_test_print_redirect(cmd);
	return (TRUE);
}

t_bool	ft_backup_fd(t_cmd *cmd)
{
	t_redirect	*greater_redir;
	t_redirect	*lesser_redir;

	greater_redir = cmd->redirect;
	lesser_redir = cmd->redirect;

	if (cmd->final_greater_fd != 0)
	{
		while(greater_redir)
		{
			if (greater_redir->right_fd == cmd->final_greater_fd)
				break;
			greater_redir = greater_redir->next;
		}
		if (dup2(greater_redir->backup_fd, 1) < 0)
		{
			ft_error_display("minishell", "dup2", 1);
			return (FALSE);
		}
	}
	if (cmd->final_lesser_fd != 0)
	{
		while(lesser_redir)
		{
			if (lesser_redir->right_fd == cmd->final_lesser_fd)
				break ;
			lesser_redir = lesser_redir->next;
		}
		if (dup2(lesser_redir->backup_fd, 0) < 0)
		{
			ft_error_display("minishell", "dup2", 1);
			return (FALSE);
		}
	}
	return (TRUE);
}


t_bool	ft_delete_tmpfile(t_cmd *cmd, int final_lesser_fd)
{
	t_redirect	*lesser_redir;

	lesser_redir = cmd->redirect;
	if (final_lesser_fd != 0)
	{
		while(lesser_redir)
		{
			if (lesser_redir->right_fd == final_lesser_fd)
				break ;
			lesser_redir = lesser_redir->next;
		}
	}
	if (lesser_redir->type == DOUBLE_LESSER)
	{
		if (unlink("tmp.txt") < 0)
		{
			ft_error_display("minishell", "dup2", 1);
			return (FALSE);
		}
	}
	return (TRUE);
}
