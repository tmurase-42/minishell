/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_duplicate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:36:11 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 20:56:26 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *ft_token_duplicate(t_token *tokens)
{
	t_token	*tmp_token;
	t_token *new_tokens;
	t_token	*new_token;

	tmp_token = ft_token_get_first(tokens);
	new_tokens = ft_token_create(tmp_token->data, tmp_token->type);
	while (tmp_token)
	{
		if (!(new_token = ft_token_create(tmp_token->data, tmp_token->type)))
			ft_error("memory has not been allocated.", EXIT_FAILURE);
		if (!(ft_token_add(new_token, &new_tokens)))
			ft_error("token can't be added.", EXIT_FAILURE);
		tmp_token = tmp_token->next;
	}
	return (new_tokens);
}
