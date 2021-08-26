/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/26 21:08:24 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*get_first_token(t_token *tokens)
{
	t_token	*target;

	if (!tokens)
		return (NULL);
	target = tokens;
	while (target->prev)
		target = target->prev;
	return (target);
}

static t_token	*get_last_token(t_token *tokens)
{
	t_token	*target;

	if (!tokens)
		return (NULL);
	target = tokens;
	while (target->next)
		target = target->next;
	return (target);
}


void			ft_token_destroy(t_token *token, t_token **tokens)
{
	t_token *first_token;
	t_token *last_token;

	first_token = NULL;
	last_token = NULL;
	if (!token || !tokens)
		return ;
	first_token = get_first_token(*tokens);
	last_token = get_last_token(*tokens);
	if (first_token != token && last_token != token)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
	}
	else if (first_token == token)
		token->next->prev = NULL;
	else if (last_token == token)
		token->prev->next = NULL;
	// ft_token_free(token);
}
