/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:16:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/05 21:28:15 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*check_redirect(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token)
	{
		if (token->type == CHAR_GREATER)
			return (token);
		if (token->next == NULL)
			break ;
		token = token->next;
	}
	return (token);
}

static void ft_test_print_redirect(t_redirect *redirect)
{
	printf("---------------\n");
	printf("redirect->right_id: %d\n" ,redirect->right_fd);
	printf("open_filepath: %s\n", redirect->open_filepath);
	printf("redirect->left_id: %d\n" ,redirect->left_fd);

}

void	ft_setup_redirect(t_cmd	*cmd)
{
	t_token	*redirect_token;
	// cmd構造体にリダイレクトの有無をチェック

	if (cmd == NULL)
		return ;
	redirect_token = check_redirect(cmd->args);
	printf("redirect_token->type = %d\n", redirect_token->type);
	if (redirect_token->type == CHAR_GREATER)
	{
		if (redirect_token->prev->type == IO_NUMBER)
			cmd->redirect->left_fd = ft_atoi(redirect_token->prev->data);
		else
			cmd->redirect->left_fd = 1;
		cmd->redirect->open_filepath = ft_strdup(redirect_token->next->data);
		cmd->redirect->right_fd = open(cmd->redirect->open_filepath, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (cmd->redirect->right_fd < 0)
			ft_error("could not open file", 1);
		ft_token_destroy(redirect_token, &cmd->args);
	}
	ft_test_print_redirect(cmd->redirect);

	return ;
}
