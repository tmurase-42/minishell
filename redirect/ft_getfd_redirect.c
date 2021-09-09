/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfd_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:16 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/09 16:56:39 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_getfd_redirect(t_cmd *cmd)
{
	t_redirect	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type == CHAR_GREATER)
		{
			redir->right_fd = open(redir->open_filepath, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			cmd->final_greater_fd = redir->right_fd;
		}
		else if (redir->type == DOUBLE_GREATER)
		{
			redir->right_fd = open(redir->open_filepath, O_RDWR | O_CREAT | O_APPEND, 0777);
			cmd->final_greater_fd = redir->right_fd;
		}
		else if (redir->type == CHAR_LESSER)
		{
			redir->right_fd = open(redir->open_filepath, O_RDWR, 0777);
			cmd->final_lesser_fd = redir->right_fd;
		}
		else if (redir->type == DOUBLE_LESSER)
		{
			///redir->right_fd = open(redir->open_filepath, O_RDWR | O_CREAT, 0777);
			redir->right_fd = open("tmp.txt", O_RDWR | O_CREAT, 0777);
			ft_dup_heredoc(redir, cmd);
			cmd->final_lesser_fd = redir->right_fd;
			//cmd->final_lesser_fd = dup(redir->right_fd);
			//close(redir->right_fd);
			//unlink("tmp.txt");
		}
		redir = redir->next;
	}
	//ft_test_print_redirect(cmd);
}

static	t_bool check_error_open_close(t_redirect *redir, int final_fd)
{
	if (redir->right_fd < 0)
	{
		ft_error_display("minishell","open", 1);
		return (FALSE);
	}
	if (redir->right_fd != final_fd)
	{
		if (close(redir->right_fd) < 0)
		{
			ft_error_display("minishell", "close", 1);
			return (FALSE);
		}
		//tmpファイルが複数ある場合の処理が実装できたらエラー判定する。
	//	if (redir->type == DOUBLE_LESSER)
	//	{
	//		if (unlink(redir->open_filepath) < 0)
	//		{
	//			ft_error_display("minishell", "unlink", 1);
	//			return (FALSE);
	//		}
	//	}
	}
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
