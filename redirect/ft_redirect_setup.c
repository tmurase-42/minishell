/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:16:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/14 11:42:30 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	check_redirect(t_cmd *cmd)
{
	t_token	*token;
	t_bool status;

	status = FALSE;
	token = cmd->args;

	while (token)
	{
		if (token->type == CHAR_GREATER || token->type == DOUBLE_GREATER)
		{
			status = TRUE;
			ft_import_redirect_information(cmd, token, 1);
		}
		if (token->type == CHAR_LESSER || token->type == DOUBLE_LESSER)
		{
			status = TRUE;
			ft_import_redirect_information(cmd, token, 0);
		}
		token = token->next;
	}
	return (status);
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
		printf("cmd->is_quot:%d\n", redirect->is_quot);
		printf("---------------\n");
		redirect = redirect->next;
	}
}

t_bool	ft_setup_redirect(t_cmd	*cmd)
{
	t_cmd	*tmp;
	t_bool	status;

	tmp = cmd;
	if (cmd == NULL)
		return (FALSE) ;
	status = check_redirect(tmp);
	while (cmd->redirect->prev != NULL)
		cmd->redirect = cmd->redirect->prev;
	return (status);
}
