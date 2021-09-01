/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_duplicate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:36:11 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/29 18:08:12 by tdofuku          ###   ########.fr       */
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


t_token *ft_token_duplicate(t_token *tokens)
{
	t_token	*tmp_token;
	t_token *new_tokens;
	t_token	*new_token;

	tmp_token = get_first_token(tokens);
	new_tokens = ft_token_create(tmp_token->data, tmp_token->type);
	while (tmp_token)
	{
		if (!(new_token = ft_token_create(tmp_token->data, tmp_token->type)))
			ft_error("Error", "memory has not been allocated.", 0);
		if (!(ft_token_add(new_token, &new_tokens)))
			ft_error("Error", "token can't be added.", 0);
		tmp_token = tmp_token->next;
	}
	return (new_tokens);
}
