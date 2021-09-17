/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_import_redirect_infor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:16:26 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 03:01:43 by tdofuku          ###   ########.fr       */
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
	t_token	*first_token;

	first_token = ft_token_get_first(redirect_token);
	if (first_token == redirect_token)
		return (TRUE);
	else
	{
		return (FALSE);
	}
	return (FALSE);
}

static void	destory_redirect_token(t_cmd *cmd,
				t_token *redirect_token, t_bool is_first)
{
	if (is_first == TRUE && cmd->argc > 2)
	{
		cmd->args = cmd->args->next;
		cmd->args->prev = NULL;
		cmd->args = cmd->args->next;
		cmd->args->prev = NULL;
	}
	else if (is_first == FALSE)
	{
		if (redirect_token->prev != NULL)
			if (redirect_token->prev->type == IO_NUMBER)
				ft_token_destroy(redirect_token->prev, &cmd->args);
		ft_token_destroy(redirect_token, &cmd->args);
		ft_token_destroy(redirect_token->next, &cmd->args);
	}
}

void	ft_import_redirect_information(t_cmd *cmd, t_token *redirect_token,
			int default_fd, t_bool status)
{
	t_redir	*tmp;
	t_bool		is_first;

	if (status == TRUE)
	{
		tmp = cmd->redirect;
		cmd->redirect->next = ft_create_redirect();
		cmd->redirect = cmd->redirect->next;
		cmd->redirect->prev = tmp;
	}
	cmd->redirect->type = redirect_token->type;
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
