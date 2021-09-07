/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/07 17:46:54 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_new_token(char *str, int i, int *word_len,
	char *quote_status, t_token_type token_type, size_t *space_len)
{
	int				word_start;
	char			*word;
	t_token			*new_token;

	word_start = 0;
	word = NULL;
	new_token = NULL;
	if (*word_len > 0)
	{
		word_start = (i - (*word_len));
		if (*quote_status == CHAR_QUOTE || *quote_status == CHAR_DQUOTE)
			word_start = (i - (*word_len + 1));
		if (token_type == CHAR_EMPTY)
			word = "\0";
		else
			word = ft_substr(str, word_start, *word_len);
		new_token = ft_token_create(word, token_type);
		new_token->space_len = *space_len;
		*word_len = 0;
		*quote_status = '\0';
		*space_len = 0;
	}
	return new_token;
}

static t_token_type	get_token_type(char c)
{
	t_token_type	token_type;

	token_type = CHAR_GENERAL;
	if (c == '|')
		token_type = CHAR_PIPE;
	else if (c == '<')
		token_type = CHAR_LESSER;
	else if (c == '>')
		token_type = CHAR_GREATER;
	else if (c == '\0')
		token_type = CHAR_NULL;
	else if (c == CHAR_QUOTE)
		token_type = CHAR_QUOTE;
	else if (c == CHAR_DQUOTE)
		token_type = CHAR_DQUOTE;
	return token_type;
}

static void	set_token_type(char *str, int *i, int *word_len,
	char *quote_status, t_token_type *token_type)
{
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
	{
		*token_type = get_token_type(str[*i]);
		*word_len += 1;
		*i += 1;
		if (str[*i] == '>' && (*word_len += 1) && (*i += 1))
			*token_type = DOUBLE_GREATER;
		if (str[*i] == '<' && (*word_len += 1) && (*i += 1))
			*token_type = DOUBLE_LESSER;
	}
	else if (str[*i] == CHAR_QUOTE || str[*i] == CHAR_DQUOTE)
	{
		*token_type = get_token_type(str[*i]);
		*quote_status = str[*i];
		if (str[*i + 1] == *quote_status && (*i += 2) && (*word_len += 1))
			*token_type = CHAR_EMPTY;
		else
			while(str[*i] != '\0')
			{
				*i += 1;
				if (str[*i] == *quote_status && (*i += 1))
					break;
				*word_len += 1;
				if (str[*i] == '\0')
					ft_error("an unclosed quote is detected.", EXIT_FAILURE);
			}
	}
	else if (ft_isdigit(str[*i]))
	{
		*token_type = CHAR_GENERAL;
		while(ft_isdigit(str[*i]))
		{
			*i += 1;
			*word_len += 1;
		}
		if (str[*i] == '>' || str[*i] == '<')
			*token_type = IO_NUMBER;
	}
}

static t_token	*split_word(char *str, int *i, int *word_len,
	char *quote_status, t_token_type *token_type)
{
	t_token			*tokens;
	size_t			space_len;

	tokens = NULL;
	space_len = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>' ||
			str[*i] == CHAR_QUOTE || str[*i] == CHAR_DQUOTE)
		{
			if (*word_len == 0)
				set_token_type(str, i, word_len, quote_status, token_type);
		}
		else if (str[*i] == CHAR_WHITESPACE || str[*i] == CHAR_TAB)
		{
			if (*word_len == 0)
			{
				space_len += 1;
				*i += 1;
			}
			*quote_status = '\0';
		}
		else if (ft_isdigit(str[*i]) && *token_type != CHAR_GENERAL)
		{
			set_token_type(str, i, word_len, quote_status, token_type);
			continue ;
		}
		else
		{
			*token_type = get_token_type(str[*i]);
			*i += 1;
			*word_len += 1;
			continue;
		}
		ft_token_add(create_new_token(str, *i, word_len, quote_status, *token_type, &space_len), &tokens);
		*token_type = CHAR_NULL;
	}
	if (*word_len > 0)
		ft_token_add(create_new_token(str, *i, word_len, quote_status, *token_type, &space_len), &tokens);
	return tokens;
}

t_token	*ft_lexer(char *str)
{
	int				i;
	int				word_len;
	char			quote_status;
	t_token_type	token_type;

	i = 0;
	word_len = 0;
	token_type = CHAR_NULL;
	quote_status = FALSE;
	if (!str)
		return NULL;
	return split_word(str, &i, &word_len, &quote_status, &token_type);
}
