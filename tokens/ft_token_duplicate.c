/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_duplicate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 17:36:11 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 22:58:04 by tdofuku          ###   ########.fr       */
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
			ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
		ft_token_add(new_token, &new_tokens);
		tmp_token = tmp_token->next;
	}
	return (new_tokens);
}
