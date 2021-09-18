/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_destory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:42:59 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 16:57:51 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_destory(t_redir *redir)
{
	free(redir->open_filepath);
	free(redir);
}

void	redirect_destroy_all(t_redir *redir)
{
	while (redir)
	{
		redirect_destory(redir);
		redir->next;
	}
}

void	ft_cmd_destory(t_cmd *cmd)
{
	while(cmd)
	{

		// token構造体をfree

		// redirect構造体をfree
		redirect_destory_all(cmd->redirect);
		//cmd構造体そのものをfree
		cmd_destroy(cmd);
		//cmd構造体を次のノードへ移動
		cmd = cmd->next;
	}
}
