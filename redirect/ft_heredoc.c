/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 20:13:07 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/14 14:39:36 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_dup_heredoc(t_redirect *redir, t_cmd *cmd)
{
	char *string;
	extern t_mshl_data	*g_mshl_data;

	string = NULL;
	while (1)
	{
		ft_sigint_setter(ft_sigint_handler);
		if (g_mshl_data->interrupted == TRUE)
			return (FALSE);
		string = readline("\e[36m>\e[0m");
		if (cmd->redirect->is_quot != SINGLE_QUOT && cmd->redirect->is_quot != DOUBLE_QUOT)
			ft_expand_str(&string);
		if (string == NULL)
			write(1, "\n", 1);
		else if (ft_strcmp(string, redir->open_filepath) == 0)
			break;
		else
		{
			write(redir->right_fd, string, ft_strlen(string));
			write(redir->right_fd, "\n", 1);
		}
	}
	return (TRUE);
}
