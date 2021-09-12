/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 20:13:07 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/12 10:40:15 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_quot(char *str)
{
	if (ft_strchr(str, 34) == NULL || ft_strchr(str, 39) == NULL)
		return (NO_QUOT);
	return (IS_QUOT);
}

void	ft_dup_heredoc(t_redirect *redir, t_cmd *cmd)
{
	char *string;
	int	is_quot_pattern;

	string = NULL;
	is_quot_pattern = is_quot(redir->open_filepath);
	while (1)
	{
		ft_sigint_setter(SIG_DFL);
		string = readline("\e[36m>\e[0m");
		if (is_quot_pattern == NO_QUOT)
			ft_expand_str(&string);
		if (string == NULL)
			write(1, "\n", 1);
		else if (ft_strncmp(string, redir->open_filepath, ft_strlen(redir->open_filepath)) == 0)
			break;
		else
		{
			write(redir->right_fd, string, ft_strlen(string));
			write(redir->right_fd, "\n", 1);
		}
	}
	(void)cmd;
}
