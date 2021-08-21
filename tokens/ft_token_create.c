/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:53:43 by tdofuku           #+#    #+#             */
/*   Updated: 2021/07/29 22:24:43 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token_create(char *data, t_token_type type)
{
	t_token	*token;

	if (!(token = malloc(sizeof(t_token))))
		ft_error(NULL, NULL, 0);
	token->data = data;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
