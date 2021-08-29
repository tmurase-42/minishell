/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/08/29 14:26:13 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_new_token(char *str, int i, int *word_len,
	char *quote_status, t_token_type token_type)
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
		word = ft_substr(str, word_start, *word_len);
		new_token = ft_token_create(word, token_type);
		*word_len = 0;
		*quote_status = '\0';
	}
	return new_token;
}

static t_token_type	get_token_type(char c)
{
	t_token_type	token_type;

	token_type = CHAR_NULL;
	if (c == '|')
		token_type = CHAR_PIPE;
	// else if (c == ';')
	//	token_type = CHAR_SEMICOLON;
	else if (c == '<')
		token_type = CHAR_LESSER;
	else if (c == '>')
		token_type = CHAR_GREATER;
	else
		token_type = CHAR_NULL;
	return token_type;
}

static void	set_token_type(char *str, int *i, int *word_len, char *quote_status, t_token_type *token_type)
{
	if (str[*i] == '|' || str[*i] == ';' || str[*i] == '<' || str[*i] == '>')
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
		*quote_status = str[*i];
		while(str[*i] != '\0')
		{
			*i += 1;
			if (str[*i] == *quote_status && (*i += 1))
				break;
			*word_len += 1;
			if (str[*i] == '\0')
				ft_error(NULL, NULL, 0);
		}
	}
}

static t_token	*split_word(char *str, int *i, int *word_len, char *quote_status, t_token_type *token_type)
{
	t_token			*tokens;

	tokens = NULL;
	while (str[*i] != '\0')
	{
		if (str[*i] == '|' || str[*i] == ';' || str[*i] == '<' || str[*i] == '>' ||
			str[*i] == CHAR_QUOTE || str[*i] == CHAR_DQUOTE)
		{
			if (*word_len == 0)
				set_token_type(str, i, word_len, quote_status, token_type);
		}
		else if (str[*i] == CHAR_WHITESPACE)
		{
			if (*word_len == 0)
				*i += 1;
			*quote_status = '\0';
		}
		else {
			*i += 1;
			*word_len += 1;
			continue;
		}
		ft_token_add(create_new_token(str, *i, word_len, quote_status, *token_type), &tokens);
	}
	if (*word_len > 0)
		ft_token_add(create_new_token(str, *i, word_len, quote_status, *token_type), &tokens);
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
