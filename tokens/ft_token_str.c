/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:01:31 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/17 22:53:06 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	token_char_empty(t_token *current_token, char **str)
{
	char	*tmp;

	if (current_token->next && current_token->next->space_len != 0)
	{
		tmp = *str;
		*str = ft_strjoin(*str, " '' ");
		free(tmp);
	}
	if (current_token->prev && current_token->prev->data != NULL
		&& current_token->prev->data[0] == '$'
		&& current_token->prev->space_len == 1)
	{
		tmp = *str;
		*str = ft_strjoin(*str, "\"\"");
		free(tmp);
	}
}

static void	token_char_general_quotes(t_token *current_token,
	char **str, t_bool edge)
{
	char	*tmp;

	if (edge == TRUE)
	{
		if (current_token->type == CHAR_DQUOTE
			|| current_token->type == CHAR_QUOTE)
		{
			tmp = *str;
			if (current_token->type == CHAR_DQUOTE)
				*str = ft_strjoin(*str, "\"");
			else
				*str = ft_strjoin(*str, "\'");
			free(tmp);
		}
	}
	else
	{
		tmp = *str;
		*str = ft_strjoin(*str, current_token->data);
		free(tmp);
	}
}

static void	token_char_general(t_token *current_token, char **str)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (current_token->space_len > i)
	{
		tmp = *str;
		*str = ft_strjoin(*str, " ");
		free(tmp);
		i++;
	}
	token_char_general_quotes(current_token, str, TRUE);
	token_char_general_quotes(current_token, str, FALSE);
	token_char_general_quotes(current_token, str, TRUE);
}

char	*ft_token_str(t_token *tokens, int start, int len)
{
	t_token	*current_token;
	int		i;
	char	*str;

	if (!tokens)
		return (NULL);
	current_token = ft_token_get_first(tokens);
	i = -1;
	while (current_token->next && (start - (++i)) > 0)
		current_token = current_token->next;
	if (current_token->data != NULL)
		str = ft_strdup(current_token->data);
	else
		str = NULL;
	current_token = current_token->next;
	i = -1;
	while (current_token && (++i) < len)
	{
		if (current_token->type == CHAR_EMPTY)
			token_char_empty(current_token, &str);
		else if (current_token->data != NULL)
			token_char_general(current_token, &str);
		current_token = current_token->next;
	}
	return (str);
}
