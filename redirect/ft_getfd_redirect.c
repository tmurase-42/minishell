/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfd_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:16 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/10 20:06:08 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_getfd_redirect(t_cmd *cmd)
{
	t_redirect	*redir;
	int	result;

	result = 0;
	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == CHAR_GREATER)
			redir->right_fd = open(redir->open_filepath, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (redir->type == DOUBLE_GREATER)
			redir->right_fd = open(redir->open_filepath, O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (redir->type == CHAR_LESSER)
			redir->right_fd = open(redir->open_filepath, O_RDWR, 0777);
		else if (redir->type == DOUBLE_LESSER)
		{
			redir->right_fd = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
			ft_dup_heredoc(redir, cmd);
			result = close(redir->right_fd);
			redir->right_fd = open("tmp.txt", O_RDWR ,0777);
			result = unlink("tmp.txt");
		}
		if (result == -1 || redir->right_fd == -1)
			return (FALSE);
		if (redir->type == CHAR_GREATER || redir->type == DOUBLE_GREATER)
			cmd->final_greater_fd = redir->right_fd;
		if (redir->type == CHAR_LESSER || redir->type == DOUBLE_LESSER)
			cmd->final_lesser_fd = redir->right_fd;
		redir = redir->next;
	}
	return (TRUE);
}

static	t_bool check_error_open_close(t_redirect *redir, int final_fd)
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
	t_redirect *redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == CHAR_GENERAL || redir->type == DOUBLE_GREATER)
			if (check_error_open_close(redir, cmd->final_greater_fd) == FALSE)
				return (FALSE);
		if (redir->type == CHAR_LESSER || redir->type == DOUBLE_LESSER)
			if (check_error_open_close(redir, cmd->final_lesser_fd) == FALSE)
				return (FALSE);
		redir = redir->next;
	}
	return (TRUE);
}