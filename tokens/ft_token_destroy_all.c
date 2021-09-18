/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_destroy_all.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:42:41 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 16:56:10 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_destroy_all(t_token **tokens)
{
	t_token	*token;

	token = ft_token_get_first(*tokens);
	while (token)
	{
		ft_token_destroy(token, tokens);
		token = token->next;
	}
	free(token);
}
