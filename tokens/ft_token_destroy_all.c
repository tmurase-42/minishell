/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_destroy_all.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:42:41 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 18:32:56 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_destroy_all(t_token **tokens)
{
	t_token	*token;
	t_token *tmp;

	token = ft_token_get_first(*tokens);
	while (token)
	{
		tmp = token->next;
		ft_token_destroy(token, tokens);
		token = tmp;
	}
	free(token);
}
