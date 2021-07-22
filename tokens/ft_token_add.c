/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/07/22 09:44:17 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_token	*get_last_token(t_token *tokens)
{
	t_token	*target;

	if (!tokens)
		return (NULL);
	target = tokens;
	while (target->next)
		target = target->next;
	return (target);
}

void			ft_token_add(t_token *new_token, t_token **tokens)
{
	t_token *last_token;

	last_token = NULL;
	if (!new_token || !tokens)
		return ;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last_token = get_last_token(*tokens);
		new_token->prev = last_token;
		last_token->next = new_token;
		new_token->next = NULL;
	}
}
