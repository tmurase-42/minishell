/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:34:08 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 18:26:53 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
	token->data = NULL;
	token->next = NULL;
	token->prev = NULL;
	token->space_len = 0;
	return (token);
}

t_redir	*ft_create_redirect(void)
{
	t_redir	*redirect;

	redirect = ft_calloc(1, sizeof(t_redir));
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

t_token	*last_token(t_token *token)
{
	t_token	*target;

	target = token;
	while (target->next)
		target = target->next;
	return (target);
}

void	add_token(t_token *copy)
{
	t_token	*next;
	t_token	*last;

	if (!copy)
		ft_error_display(NULL, "Not extpected error", EXIT_FAILURE);
	next = create_token();
	last = last_token(copy);
	last->next = next;
	next->prev = last;
}
