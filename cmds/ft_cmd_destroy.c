/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:42:59 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/20 10:47:41 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_destroy(t_redir *redir)
{
	free(redir->open_filepath);
	free(redir);
}

void	redirect_destroy_all(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		redirect_destroy(redir);
		redir = tmp;
	}
}

void	ft_cmd_destroy(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		ft_token_free(cmd->args);
		redirect_destroy_all(cmd->redirect);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}
