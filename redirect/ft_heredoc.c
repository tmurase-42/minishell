/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 20:13:07 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/08 09:48:55 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_heredoc(t_cmd *cmd)
{
	int	fd;
	char *string;

	fd = cmd->redirect->left_fd;

	string = NULL;
	while (42)
	{
		ft_sigint_setter(SIG_DFL);
		string = readline("\e[36m>\e[0m");
		if (string == NULL)
			write(1, "\n", 1);
		else if (ft_strncmp(string, cmd->redirect->open_filepath, ft_strlen(cmd->redirect->open_filepath)) == 0)
			break;
		else
			write(fd, string, ft_strlen(string) + 1);
	}
}
