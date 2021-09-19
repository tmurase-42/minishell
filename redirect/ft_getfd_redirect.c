/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfd_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:16 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/19 17:42:01 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_tmpfile(t_cmd *cmd, t_redir *redir, int result, int num)
{
	char	*tmpfilename;
	char	*tmp;
	char	*numstr;

	tmpfilename = ft_strdup("tmpfile_0");
	tmp = ft_strchr(tmpfilename, '0');
	numstr = ft_itoa(num);
	ft_strlcpy(tmp, numstr, 2);
	redir->right_fd = open(tmpfilename, O_RDWR | O_CREAT, 0777);
	if (ft_dup_heredoc(redir, cmd) == TRUE)
	{
		result = close(redir->right_fd);
		redir->right_fd = open(tmpfilename, O_RDWR, 0777);
		result = unlink(tmpfilename);
	}
	else
		result = unlink(tmpfilename);
	free(tmpfilename);
	free(numstr);
	return (result);
}

static	t_bool	create_files(t_cmd *cmd, t_redir *redir, int result, int num)
{
	if (redir->type == CHAR_GREATER)
		redir->right_fd = open(redir->open_filepath,
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (redir->type == DOUBLE_GREATER)
		redir->right_fd = open(redir->open_filepath,
				O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (redir->type == CHAR_LESSER)
		redir->right_fd = open(redir->open_filepath,
				O_RDWR, 0777);
	else if (redir->type == DOUBLE_LESSER)
	{
		result = create_tmpfile(cmd, redir, result, num);
		num++;
	}
	if ((result == -1) || (redir->right_fd == -1 && redir->type != CHAR_LESSER))
		return (FALSE);
	return (TRUE);
}

t_bool	ft_getfd_redirect(t_cmd *cmd)
{
	t_redir	*redir;
	int		result;
	int		num;

	result = 0;
	num = 1;
	redir = cmd->redirect;
	while (redir)
	{
		if (create_files(cmd, redir, result, num) == FALSE)
			return (FALSE);
		if (redir->type == CHAR_GREATER || redir->type == DOUBLE_GREATER)
			cmd->final_greater_fd = redir->right_fd;
		if (redir->type == CHAR_LESSER || redir->type == DOUBLE_LESSER)
			cmd->final_lesser_fd = redir->right_fd;
		redir = redir->next;
	}
	return (TRUE);
}
