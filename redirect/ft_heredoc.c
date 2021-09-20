/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 20:13:07 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/20 13:21:00 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	check_write(t_redir *redir, char *str)
{
	if (str == NULL)
		return (FALSE);
	if (ft_strcmp(str, redir->open_filepath, ft_max(ft_strlen(str),
				ft_strlen(redir->open_filepath))) == 0)
		return (FALSE);
	else
	{
		write(redir->right_fd, str, ft_strlen(str));
		write(redir->right_fd, "\n", 1);
	}
	return (TRUE);
}

t_bool	ft_dup_heredoc(t_redir *redir, t_cmd *cmd)
{
	extern t_mshl_data	*g_mshl_data;
	char				*str;

	while (1)
	{
		ft_sigint_setter(ft_sigint_handler);
		if (g_mshl_data->interrupted == TRUE)
		{
			g_mshl_data->command = str;
			return (FALSE);
		}
		str = readline("\e[36m>\e[0m");
		if (cmd->redirect->is_quot != SINGLE_QUOT
			&& cmd->redirect->is_quot != DOUBLE_QUOT)
			ft_expand_str(&str);
		if (check_write(redir, str) == FALSE)
			break ;
		free(str);
	}
	free(str);
	return (TRUE);
}
