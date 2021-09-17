/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/17 22:18:46 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_add(t_token *new_token, t_token **tokens)
{
	t_token	*last_token;

	last_token = NULL;
	if (!new_token || !tokens)
		return ;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last_token = ft_token_get_last(*tokens);
		new_token->prev = last_token;
		last_token->next = new_token;
		new_token->next = NULL;
	}
}
