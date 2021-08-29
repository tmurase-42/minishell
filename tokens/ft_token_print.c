/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/29 16:08:07 by tdofuku          ###   ########.fr       */
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

void			ft_token_print(t_token *tokens)
{
	t_token	*current_token;
	int		i;

	i = 0;
	if (!tokens)
		return ;
	else
	{
		current_token = get_first_token(tokens);
		printf("--------------------------------------\n");
		printf("index : type : data\n");
		while(current_token) {
			printf("%5d : %4d : %s\n", i, current_token->type, current_token->data);
			current_token = current_token->next;
			i++;
		}
		printf("--------------------------------------\n");
	}
}
