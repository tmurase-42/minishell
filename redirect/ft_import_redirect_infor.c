/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_import_redirect_infor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:16:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/14 11:42:39 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	ft_import_redirect_information(t_cmd *cmd, t_token *redirect_token, int default_fd)
{
	t_redirect	*tmp;

	//新しい連結リストのリダイレクト構造体を生成している。
	if (cmd->redirect->open_filepath != NULL)
	{
		tmp = cmd->redirect;
		cmd->redirect->next = ft_create_redirect();
		cmd->redirect = cmd->redirect->next;
		cmd->redirect->prev = tmp;
	}
	//tokenのタイプをリダイレクト構造体に代入している。
	cmd->redirect->type = redirect_token->type;

	//リダイレクトの左側のfdの値をリダイレクト構造体に代入している。
	if (redirect_token->prev == NULL)
		cmd->redirect->left_fd = default_fd;
	else if (redirect_token->prev->type == IO_NUMBER)
		cmd->redirect->left_fd = ft_atoi(redirect_token->prev->data);
	else
		cmd->redirect->left_fd = default_fd;

	//リダイレクトするファイル名を生成している。
	if (redirect_token->next != NULL)
		cmd->redirect->open_filepath = ft_strdup(redirect_token->next->data);

	//リダイレクトの区切り文字が、クォーとで囲まれていたかどうかを判断するために、代入している。
	cmd->redirect->is_quot = redirect_token->next->type;

	//文字列の取得に失敗したら、エラーを吐くようにしている。
	if (cmd->redirect->open_filepath == NULL)
		ft_error_display("ft_strdup", "failed to get open_filepath", 1);

	//リダイレクトの左隣に数字が入っていた場合は、削除する。
	if (redirect_token->prev != NULL)
		if (redirect_token->prev->type == IO_NUMBER)
			ft_token_destroy(redirect_token->prev, &cmd->args);
	//リダイレクトの値を削除する
	ft_token_destroy(redirect_token, &cmd->args);
	//リダイレクトの右隣の文字列を削除する。
	ft_token_destroy(redirect_token->next, &cmd->args);
}
