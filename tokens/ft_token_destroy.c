/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/19 16:15:04 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_destroy(t_token *token, t_token **tokens)
{
	if (!token || !tokens)
		return ;
	if (token->prev && token->next)
	{
		token->prev->next = token->next;
		token->next->prev = token->prev;
		free(token->data);
		free(token);
	}
	else if (token->prev == NULL && token->next)
	{
		token->next->prev = NULL;
		*tokens = token->next;
		free(token->data);
		free(token);
	}
	else if (token->next == NULL && token->prev)
	{
		token->prev->next = NULL;
		free(token->data);
		free(token);
	}
}
