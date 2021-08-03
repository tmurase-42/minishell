/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:53:43 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/03 21:05:22 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_token	*get_first_token(t_token *tokens)
{
	t_token	*target;

	if (!tokens)
		return (NULL);
	target = tokens;
	while (target->prev)
		target = target->prev;
	return (target);
}

void	ft_token_free(t_token *tokens)
{
	t_token	*cur_token;
	t_token *tmp_token;

	if (!tokens)
		return ;
	cur_token = get_first_token(tokens);
	while(cur_token)
	{
		tmp_token = cur_token;
		cur_token = cur_token->next;
		// free(tmp_token->data);
		free(tmp_token);
	}
	return ;
}
