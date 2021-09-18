/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:42:59 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 17:24:46 by tmurase          ###   ########.fr       */
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
	t_redir *tmp;
	while (redir)
	{
		tmp = redir->next;
		redirect_destroy(redir);
		redir = tmp;
	}
}

void	ft_cmd_destroy(t_cmd *cmd)
{
	t_cmd *tmp;
	while(cmd)
	{

		// token構造体をfree
		ft_token_destroy_all(&cmd->args);
		// redirect構造体をfree
		redirect_destroy_all(cmd->redirect);
		//cmd構造体そのものをfree
		tmp = cmd->next;
		free(cmd);
		//cmd構造体を次のノードへ移動
		cmd = tmp;
	}
}
