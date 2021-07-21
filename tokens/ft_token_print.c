/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/07/17 16:49:22 by tdofuku          ###   ########.fr       */
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
		while(current_token) {
			ft_putnbr_fd(i, STDOUT_FILENO);
			ft_putstr_fd(": ", STDOUT_FILENO);
			ft_putstr_fd(current_token->data, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			current_token = current_token->next;
			i++;
		}
	}
}
