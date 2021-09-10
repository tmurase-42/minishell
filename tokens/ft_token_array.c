/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 20:56:26 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			**ft_token_array(t_token *tokens, int start, int len)
{
	t_token	*current_token;
	int		i;
	int		token_length;
	char	**table;

	if (!tokens)
		return NULL;
	token_length = ft_token_length(tokens);
	current_token = ft_token_get_first(tokens);
	if (!(table = ft_calloc(token_length + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	while(current_token->next && (start - i) > 0 )
	{
		current_token = current_token->next;
		i++;
	}
	i = 0;
	while (current_token && i < len)
	{
		table[i] = ft_strdup(current_token->data);
		current_token = current_token->next;
		i++;
	}
	return table;
}
