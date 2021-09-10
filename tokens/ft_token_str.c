/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/10 20:56:26 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*ft_token_str(t_token *tokens, int start, int len)
{
	t_token	*current_token;
	int		i;
	size_t	j;
	int		token_length;
	char	*str;
	char	*tmp;

	if (!tokens)
		return NULL;
	token_length = ft_token_length(tokens);
	current_token = ft_token_get_first(tokens);
	i = 0;
	while(current_token->next && (start - i) > 0 )
	{
		current_token = current_token->next;
		i++;
	}
	str = current_token->data;
	current_token = current_token->next;
	i = 1;
	// printf("str: len:%d\n", len);
	while (current_token && i < len)
	{
		// printf("str: str:%s\n", str);
		if (current_token->type == CHAR_EMPTY)
		{
			if (current_token->next && current_token->next->space_len != 0)
			{
				tmp = str;
				str = ft_strjoin(str, " '' ");
				free(tmp);
			}
		}
		else
		{
			// tmp = str;
			// str = ft_strjoin(str, " '");
			// free(tmp);

			// tmp = str;
			// str = ft_strjoin(str, current_token->data);
			// free(tmp);

			// tmp = str;
			// str = ft_strjoin(str, "'");
			// free(tmp);
			j = 0;
			while(current_token->space_len > j)
			{
				tmp = str;
				str = ft_strjoin(str, " ");
				free(tmp);
				j++;
			}
			if(current_token->type == CHAR_DQUOTE || current_token->type == CHAR_QUOTE) {
				tmp = str;
				str = ft_strjoin(str, (current_token->type == CHAR_DQUOTE ? "\"" : "'"));
				free(tmp);
			}
			tmp = str;
			str = ft_strjoin(str, current_token->data);
			free(tmp);
			if(current_token->type == CHAR_DQUOTE || current_token->type == CHAR_QUOTE) {
				tmp = str;
				str = ft_strjoin(str, (current_token->type == CHAR_DQUOTE ? "\"" : "'"));
				free(tmp);
			}
		}
		current_token = current_token->next;
		i++;
	}
	return str;
}
