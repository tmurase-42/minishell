/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:34:08 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/13 14:41:37 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token *create_token(void)
{
	t_token *token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
	token->data = NULL;
	token->next = NULL;
	token->prev = NULL;
	token->space_len = 0;
	return (token);
}

t_redirect	*ft_create_redirect(void)
{
	t_redirect *redirect;

	redirect = ft_calloc(1, sizeof(t_redirect));
	redirect->backup_fd = -2;
	redirect->left_fd = -2;
	redirect->right_fd = -2;
	redirect->type = 0;
	redirect->is_quot = 0;
	redirect->open_filepath = NULL;
	redirect->next = NULL;
	redirect->prev = NULL;
	return (redirect);
}

t_cmd	*ft_cmd_lstnew(void)
{
	t_cmd	*value;

	value = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (value == NULL)
		return (NULL);
	value->args = NULL;
	value->next = NULL;
	value->args = create_token();
	value->argc = 0;
	value->pid = 0;
	value->final_greater_fd = 0;
	value->final_lesser_fd = 0;
	value->redirect = ft_create_redirect();
	return (value);
}

static t_token *last_token(t_token *token)
{
	t_token *target;

	target = token;
	while (target->next)
		target = target->next;
	return (target);
}

static void add_token(t_token *copy)
{
	t_token *next;
	t_token *last;

	if (!copy)
		ft_error(NULL, "Not extpected error", EXIT_FAILURE);
	next = create_token();
	last = last_token(copy);
	last->next = next;
	next->prev = last;
}

static t_token *copy_token(t_token *token)
{
	t_token *copy;
	t_token *tmp;

	copy = create_token();
	tmp = create_token();
	copy = tmp;
	while (token)
	{
		tmp->data = ft_strdup(token->data);
		tmp->type = token->type;
		tmp->space_len = token->space_len;
		if (token->next == NULL)
			break ;
		if (ft_strncmp(token->next->data, "|", 2) == 0)
			break;
		add_token(tmp);
		token = token->next;
		tmp = tmp->next;
	}
	return (copy);
}

static t_token *shave_token_until_pipe(t_token *token)
{
	t_token *tmp;

	tmp = create_token();
	while (token->next != NULL)
	{
		//free(token->data);
		//token->data = NULL;
		token = token->next;
		if (ft_strncmp(token->prev->data, "|", 2) == 0)
			break ;
	}

	return (token);
}

static t_bool		ft_check_pipe(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_strncmp(tmp->data, "|", 1) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

t_cmd	*ft_parser(t_token *token, t_cmd *cmd)
{
	t_cmd	*next;

	//引数のtokenが連結リストになっているときにコマンド構造体にコピーする。
	if (ft_check_pipe(token) == TRUE)
	{
		cmd->args = copy_token(token);
		cmd->argc = ft_token_length(cmd->args);
		token = shave_token_until_pipe(token);
		next = ft_cmd_lstnew();
		cmd->next = next;
		ft_parser(token, next);
	}
	else
	{
		cmd->args = copy_token(token);
		cmd->argc = ft_token_length(cmd->args);
	}

	return (cmd);
}
