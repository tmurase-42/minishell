/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfd_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:16 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/11 16:14:13 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_tmpfile(t_cmd *cmd, t_redirect *redir, int result, int num)
{
	char *tmpfilename;
	char *tmp;
	char *numstr;

	tmpfilename = ft_strdup("tmpfile_0");
	tmp = ft_strchr(tmpfilename, '0');
	numstr = ft_itoa(num);
	ft_strlcpy(tmp, numstr, 2);
	redir->right_fd = open(tmpfilename, O_RDWR | O_CREAT , 0777);
	ft_dup_heredoc(redir, cmd);
	result = close(redir->right_fd);
	redir->right_fd = open(tmpfilename, O_RDWR ,0777);
	result = unlink(tmpfilename);
	free(tmpfilename);
	return (result);
}

t_bool	ft_getfd_redirect(t_cmd *cmd)
{
	t_redirect	*redir;
	int	result;
	int	num;

	result = 0;
	num = 1;
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
			result = create_tmpfile(cmd, redir, result, num);
			num++;
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
