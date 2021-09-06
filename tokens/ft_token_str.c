/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/05 23:37:48 by tdofuku          ###   ########.fr       */
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

char			*ft_token_str(t_token *tokens, int start, int len)
{
	t_token	*current_token;
	int		i;
	int		token_length;
	char	*str;
	char	*tmp;

	if (!tokens)
		return NULL;
	token_length = ft_token_length(tokens);
	current_token = get_first_token(tokens);
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
			tmp = str;
			str = ft_strjoin(str, " '' ");
			free(tmp);
		}
		else
		{
			//tmp = str;
			//str = ft_strjoin("'", str);
			//free(tmp);

			// tmp = str;
			// str = ft_strjoin(str, " '");
			// free(tmp);

			// tmp = str;
			// str = ft_strjoin(str, current_token->data);
			// free(tmp);

			// tmp = str;
			// str = ft_strjoin(str, "'");
			// free(tmp);

			tmp = str;
			str = ft_strjoin(str, " ");
			free(tmp);
			tmp = str;
			str = ft_strjoin(str, current_token->data);
			free(tmp);
		}
		current_token = current_token->next;
		i++;
	}
	return str;
}
