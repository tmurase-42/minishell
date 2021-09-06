/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:16:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/06 16:09:10 by tmurase          ###   ########.fr       */
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
		if (token->type == DOUBLE_GREATER)
			return (token);
		if (token->type == CHAR_LESSER)
			return (token);
		if (token->type == DOUBLE_LESSER)
			return (token);
		if (token->next == NULL)
			break ;
		token = token->next;
	}
	return (token);
}

void ft_test_print_redirect(t_redirect *redirect)
{
	printf("---------------\n");
	printf("redirect->left_id: %d\n" ,redirect->left_fd);
	printf("redirect->right_id: %d\n" ,redirect->right_fd);
	printf("open_filepath:%s\n", redirect->open_filepath);

}

static void	import_redirect_information(t_cmd *cmd, t_token *redirect_token, int default_fd)
{
	cmd->redirect->type = redirect_token->type;
	if (redirect_token->prev->type == IO_NUMBER)
		cmd->redirect->left_fd = ft_atoi(redirect_token->prev->data);
	else
		cmd->redirect->left_fd = default_fd;
	cmd->redirect->open_filepath = ft_strdup(redirect_token->next->data);
	if (redirect_token->type == CHAR_GREATER || redirect_token->type == CHAR_LESSER || redirect_token->type == DOUBLE_LESSER)
		cmd->redirect->right_fd = open(cmd->redirect->open_filepath, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (redirect_token->type == DOUBLE_GREATER)
		cmd->redirect->right_fd = open(cmd->redirect->open_filepath, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (cmd->redirect->right_fd < 0)
		return (ft_error_display("No such file or directory!", cmd->redirect->open_filepath, 1));
	if (redirect_token->prev->type == IO_NUMBER)
		ft_token_destroy(redirect_token->prev, &cmd->args);
	ft_token_destroy(redirect_token, &cmd->args);
	ft_token_destroy(redirect_token->next, &cmd->args);
}

t_bool	ft_setup_redirect(t_cmd	*cmd)
{
	t_token	*redirect_token;
	// cmd構造体にリダイレクトの有無をチェック

	if (cmd == NULL)
		return (FALSE) ;
	redirect_token = check_redirect(cmd->args);
	if (redirect_token == NULL)
		return (FALSE);
	if (redirect_token->type == CHAR_GREATER || redirect_token->type == DOUBLE_GREATER)
		import_redirect_information(cmd, redirect_token, 1);
	else if (redirect_token->type == CHAR_LESSER || redirect_token->type == DOUBLE_LESSER)
		import_redirect_information(cmd, redirect_token, 0);
	//ft_test_print_redirect(cmd->redirect);
	//ft_token_print(cmd->args);
	return (TRUE);
}
