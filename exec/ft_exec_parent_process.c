/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_parent_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:27:55 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/04 09:47:50 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_parent_process(int new_pipe[], int old_pipe[], t_cmd *cmd,
	pid_t pid)
{
	extern t_mshl_data	*g_mshl_data;

	// sigintを無視する
	ft_sigint_setter(SIG_IGN);
	// 新しいパイプを、古いパイプとして保存
	ft_pipe_update(g_mshl_data->pipe_state, old_pipe, new_pipe);
	// パイプのステータスの更新
	ft_pipe_update_state(cmd);
	// プロセスidを保存
	cmd->pid = pid;
}
