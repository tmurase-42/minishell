/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:53:43 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 23:08:44 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token_create(char *data, t_token_type type)
{
	t_token	*token;

	if (!(token = ft_calloc(sizeof(t_token),1)))
		ft_error(NULL, "Memory cound not be allocated.", EXIT_FAILURE);
	token->data = data;
	token->type = type;
	token->space_len = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
