/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 20:13:07 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/08 17:21:46 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_heredoc(t_redirect *redir)
{
	int	fd;
	char *string;

	fd = redir->right_fd;
	string = NULL;
	while (1)
	{
		ft_sigint_setter(SIG_DFL);
		string = readline("\e[36m>\e[0m");
		if (string == NULL)
			write(1, "\n", 1);
		else if (ft_strncmp(string, redir->open_filepath, ft_strlen(redir->open_filepath)) == 0)
			break;
		else
			write(fd, string, ft_strlen(string));
	}
}
