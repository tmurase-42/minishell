/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:53:43 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 23:26:09 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_free(t_token *tokens)
{
	t_token	*cur_token;
	t_token	*tmp_token;

	if (tokens == NULL)
		return ;
	cur_token = ft_token_get_first(tokens);
	while (cur_token)
	{
		tmp_token = cur_token;
		cur_token = cur_token->next;
		free(tmp_token->data);
		free(tmp_token);
	}
	return ;
}
