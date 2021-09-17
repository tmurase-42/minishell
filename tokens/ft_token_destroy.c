/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/17 22:24:39 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_destroy(t_token *token, t_token **tokens)
{
	t_token	*first_token;
	t_token	*last_token;

	first_token = NULL;
	last_token = NULL;
	if (!token || !tokens)
		return ;
	first_token = ft_token_get_first(*tokens);
	last_token = ft_token_get_last(*tokens);
	if (first_token != token && last_token != token)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
	}
	else if (first_token == token && token->next)
		token->next->prev = NULL;
	else if (last_token == token && token->prev)
		token->prev->next = NULL;
}
