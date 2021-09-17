/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/17 22:32:04 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_print(t_token *tokens)
{
	t_token	*current_token;
	int		i;

	i = 0;
	if (!tokens)
		return ;
	else
	{
		current_token = ft_token_get_first(tokens);
		printf("--------------------------------------\n");
		printf("index : type : space_len : data\n");
		while (current_token)
		{
			printf(
				"%5d : %4d : %9zu : %s\n",
				i,
				current_token->type,
				current_token->space_len,
				current_token->data);
			current_token = current_token->next;
			i++;
		}
		printf("--------------------------------------\n");
	}
}
