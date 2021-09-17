/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:09:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/17 10:07:50 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	ft_check_pipe_error(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (ft_strchr(tmp->data, '|') != NULL)
	{
		return (FALSE);
	}
	while (tmp->next != NULL)
	{
		if (ft_strchr(tmp->data, '|') != NULL
			&& ft_strchr(tmp->next->data, '|') != NULL)
		{
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

static t_bool	ft_check_redirect_error(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp->next != NULL)
	{
		if (tmp->type != CHAR_GENERAL && tmp->next->type == CHAR_PIPE)
		{
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

static t_bool	ft_check_expect_let(t_token *tokens)
{
	while (tokens && !ft_check_quot(tokens->data))
	{
		if (ft_isalnum_str(tokens->data) != TRUE)
		{
			return (FALSE);
		}
		tokens = tokens->next;
	}
	return (TRUE);
}

static t_bool	ft_check_unexpect_error(t_token *tokens)
{
	while (tokens->next != NULL)
		tokens = tokens->next;
	if (tokens->type != CHAR_GENERAL && tokens->type != DOUBLE_QUOT
		&& tokens->type != SINGLE_QUOT && tokens->type != CHAR_EMPTY)
	{
		return (FALSE);
	}
	return (TRUE);
}

t_bool	ft_validate_token(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (FALSE);
	tmp = tokens;
	if (ft_check_pipe_error(tmp) != TRUE)
		return (FALSE);
	if (ft_check_redirect_error(tmp) != TRUE)
		return (FALSE);
	if (ft_check_expect_let(tmp) != TRUE)
		return (FALSE);
	if (ft_check_unexpect_error(tmp) != TRUE)
		return (FALSE);
	return (TRUE);
}
