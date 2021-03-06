/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_import_redirect_infor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:16:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/19 22:25:04 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	import_left_fd(t_token *redirect_token, int default_fd)
{
	if (redirect_token->prev == NULL)
		return (default_fd);
	else if (redirect_token->prev->type == IO_NUMBER)
		return (ft_atoi(redirect_token->prev->data));
	else
		return (default_fd);
}

t_bool	check_is_tokenfirst(t_token *redirect_token)
{
	if (redirect_token == NULL)
		return (FALSE);
	if (redirect_token->prev == NULL)
		return (TRUE);
	else
		return (FALSE);
}

static void	destory_redirect_token(t_cmd *cmd,
				t_token *redirect_token, t_bool is_first)
{
	if (is_first == TRUE && cmd->argc > 2)
	{
		ft_token_destroy(cmd->args->next, &cmd->args);
		ft_token_destroy(cmd->args, &cmd->args);
	}
	else if (is_first == FALSE)
	{
		if (redirect_token->prev != NULL)
			if (redirect_token->prev->type == IO_NUMBER)
				ft_token_destroy(redirect_token->prev, &cmd->args);
		ft_token_destroy(redirect_token->next, &cmd->args);
		ft_token_destroy(redirect_token, &cmd->args);
	}
}

void	ft_import_redirect_information(t_cmd *cmd, t_token *redirect_token,
			int default_fd, t_bool status)
{
	t_redir	*tmp;
	t_bool	is_first;

	if (status == TRUE)
	{
		tmp = cmd->redirect;
		cmd->redirect->next = ft_create_redirect();
		cmd->redirect = cmd->redirect->next;
		cmd->redirect->prev = tmp;
	}
	cmd->redirect->type = redirect_token->type;
	cmd->redirect->l_type = default_fd;
	if (redirect_token->next != NULL)
		cmd->redirect->is_quot = redirect_token->next->type;
	cmd->redirect->left_fd = import_left_fd(redirect_token, default_fd);
	if (redirect_token->next != NULL)
		cmd->redirect->open_filepath = ft_strdup(redirect_token->next->data);
	else
		cmd->redirect->open_filepath = ft_strdup("");
	if (cmd->redirect->open_filepath == NULL)
		ft_error_display("ft_strdup", "failed to get open_filepath", 1);
	is_first = check_is_tokenfirst(redirect_token);
	destory_redirect_token(cmd, redirect_token, is_first);
}
