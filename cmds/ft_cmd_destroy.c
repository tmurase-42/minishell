/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_destory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:42:59 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 17:10:28 by tmurase          ###   ########.fr       */
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
	while (redir)
	{
		redirect_destroy(redir);
		redir = redir->next;
	}
}

void	ft_cmd_destroy(t_cmd *cmd)
{
	while(cmd)
	{

		// token構造体をfree
		ft_token_destroy_all(&cmd->args);
		// redirect構造体をfree
		redirect_destroy_all(cmd->redirect);
		//cmd構造体そのものをfree
		free(cmd);
		//cmd構造体を次のノードへ移動
		cmd = cmd->next;
	}
}
