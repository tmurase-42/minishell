/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:16:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/08 21:04:42 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_redirect(t_cmd *cmd)
{
	t_token *token;
	t_redirect	*tmp;

	token = cmd->args;
	while (token)
	{
		if (token->type == CHAR_GREATER || token->type == DOUBLE_GREATER)
		{
			if (cmd->redirect->open_filepath != NULL)
			{
				tmp = cmd->redirect;
				cmd->redirect->next = ft_create_redirect();
				cmd->redirect = cmd->redirect->next;
				cmd->redirect->prev = tmp;
			}
			ft_import_redirect_information(cmd, token, 1);
		}
		if (token->type == CHAR_LESSER || token->type == DOUBLE_LESSER)
		{
			if (cmd->redirect->open_filepath != NULL)
			{
				tmp = cmd->redirect;
				cmd->redirect->next = ft_create_redirect();
				cmd->redirect = cmd->redirect->next;
				cmd->redirect->prev = tmp;
			}
			ft_import_redirect_information(cmd, token, 0);
		}
		token = token->next;
	}
}

void ft_test_print_redirect(t_cmd *cmd)
{
	t_redirect *redirect = cmd->redirect;
	while (redirect)
	{
		printf("redirect->left_id: %d\n" ,redirect->left_fd);
		printf("redirect->right_id: %d\n" ,redirect->right_fd);
		printf("redirect->type: %d\n", redirect->type);
		printf("open_filepath:%s\n", redirect->open_filepath);
		printf("cmd->final_grater_fd:%d\n", cmd->final_greater_fd);
		printf("cmd->final_lesser_fd:%d\n", cmd->final_lesser_fd);
		printf("---------------\n");
		redirect = redirect->next;
	}
}

void	ft_import_redirect_information(t_cmd *cmd, t_token *redirect_token, int default_fd)
{

	cmd->redirect->type = redirect_token->type;
	if (redirect_token->prev->type == IO_NUMBER)
		cmd->redirect->left_fd = ft_atoi(redirect_token->prev->data);
	else
		cmd->redirect->left_fd = default_fd;
	cmd->redirect->open_filepath = ft_strdup(redirect_token->next->data);
	if (redirect_token->prev->type == IO_NUMBER)
		ft_token_destroy(redirect_token->prev, &cmd->args);
	ft_token_destroy(redirect_token, &cmd->args);
	ft_token_destroy(redirect_token->next, &cmd->args);
}

t_bool	ft_setup_redirect(t_cmd	*cmd)
{
	t_cmd	*tmp;
	// cmd構造体にリダイレクトの有無をチェック
	tmp = cmd;
	if (cmd == NULL)
		return (FALSE) ;
	check_redirect(tmp);
	while (cmd->redirect->prev != NULL)
		cmd->redirect = cmd->redirect->prev;
	//ft_test_print_redirect(cmd->redirect);
	//ft_token_print(cmd->args);
	return (TRUE);
}
