/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:58:56 by tmurase           #+#    #+#             */
/*   Updated: 2021/09/18 22:00:37 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*create_new_token(t_lexer *l)
{
	int		word_start;
	char	*word;
	t_token	*new_token;

	word_start = 0;
	word = NULL;
	new_token = NULL;
	if (l->word_len > 0)
	{
		word_start = (l->i - (l->word_len));
		if (l->quote_status == CHAR_QUOTE || l->quote_status == CHAR_DQUOTE)
			word_start = (l->i - (l->word_len + 1));
		if (l->token_type == CHAR_EMPTY)
			word = ft_strdup("\0");
		else
			word = ft_substr(l->str, word_start, l->word_len);
		new_token = ft_token_create(word, l->token_type);
		new_token->space_len = l->space_len;
		l->word_len = 0;
		l->space_len = 0;
		l->quote_status = FALSE;
		free(word);
	}
	return (new_token);
}

static t_token	*split_word(t_lexer *l)
{
	t_token			*tokens;

	tokens = NULL;
	while (l->str[l->i] != '\0')
	{
		if (l->str[l->i] == '|' || l->str[l->i] == '<' || l->str[l->i] == '>')
			set_token_redirects(l);
		else if (l->str[l->i] == CHAR_QUOTE || l->str[l->i] == CHAR_DQUOTE)
			set_token_quotes(l);
		else if (l->str[l->i] == CHAR_WHITESPACE || l->str[l->i] == CHAR_TAB)
			set_token_spaces(l);
		else
		{
			if (ft_isdigit(l->str[l->i]) && l->token_type != CHAR_GENERAL)
				set_token_digits(l);
			else
				set_token_general(l);
			continue ;
		}
		ft_token_add(create_new_token(l), &tokens);
		l->token_type = CHAR_NULL;
	}
	if (l->word_len > 0)
		ft_token_add(create_new_token(l), &tokens);
	return (tokens);
}

t_token	*ft_lexer(const char *str)
{
	t_lexer	*l;
	t_token	*tokens;

	if (!str)
		return (NULL);
	l = ft_calloc(sizeof(t_lexer), 1);
	l->i = 0;
	l->word_len = 0;
	l->token_type = CHAR_NULL;
	l->quote_status = FALSE;
	l->str = str;
	l->space_len = 0;
	tokens = split_word(l);
	free(l);
	return (tokens);
}
