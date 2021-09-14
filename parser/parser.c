/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:34:08 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/14 22:52:52 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*copy_token(t_token *token)
{
	t_token	*copy;
	t_token	*tmp;

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
			break ;
		add_token(tmp);
		token = token->next;
		tmp = tmp->next;
	}
	return (copy);
}

static t_token	*shave_token_until_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = create_token();
	while (token->next != NULL)
	{
		token = token->next;
		if (ft_strncmp(token->prev->data, "|", 2) == 0)
			break ;
	}
	return (token);
}

static t_bool	ft_check_pipe(t_token *token)
{
	t_token	*tmp;

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
