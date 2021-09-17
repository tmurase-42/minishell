/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 00:29:55 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 00:52:06 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_token_redirects(t_lexer *l)
{
	if ((l->str[l->i] == '|' || l->str[l->i] == '<' || l->str[l->i] == '>')
		&& l->word_len == 0)
	{
		if (l->str[l->i] == '|')
			l->token_type = CHAR_PIPE;
		else if (l->str[l->i] == '<')
			l->token_type = CHAR_LESSER;
		else if (l->str[l->i] == '>')
			l->token_type = CHAR_GREATER;
		else
			l->token_type = CHAR_GENERAL;
		l->word_len += 1;
		l->i += 1;
		if (l->str[l->i] == '>' && l->token_type == CHAR_GREATER)
			l->token_type = DOUBLE_GREATER;
		if (l->str[l->i] == '<' && l->token_type == CHAR_LESSER)
			l->token_type = DOUBLE_LESSER;
		if (l->token_type == DOUBLE_GREATER || l->token_type == DOUBLE_LESSER)
		{
			l->word_len += 1;
			l->i += 1;
		}
	}
}

void	set_token_quotes(t_lexer *l)
{
	if ((l->str[l->i] == CHAR_QUOTE || l->str[l->i] == CHAR_DQUOTE)
		&& l->word_len == 0)
	{
		l->token_type = l->str[l->i];
		l->quote_status = l->str[l->i];
		if (l->str[l->i + 1] == l->quote_status)
		{
			l->i += 2;
			l->word_len += 1;
			l->token_type = CHAR_EMPTY;
		}
		else
		{
			while (l->str[l->i] != '\0')
			{
				l->i += 1;
				if (l->str[l->i] == l->quote_status)
				{
					l->i += 1;
					break ;
				}
				l->word_len += 1;
			}
		}
	}
}

void	set_token_digits(t_lexer *l)
{
	if (ft_isdigit(l->str[l->i]))
	{
		l->token_type = CHAR_GENERAL;
		while (ft_isdigit(l->str[l->i]))
		{
			l->i += 1;
			l->word_len += 1;
		}
		if (l->str[l->i] == '>' || l->str[l->i] == '<')
			l->token_type = IO_NUMBER;
	}
}

void	set_token_spaces(t_lexer *l)
{
	if (l->word_len == 0)
	{
		l->space_len += 1;
		l->i += 1;
	}
	l->quote_status = '\0';
}

void	set_token_general(t_lexer *l)
{
	if (l->str[l->i] == '\0')
		l->token_type = CHAR_NULL;
	if (l->str[l->i] == CHAR_QUOTE)
		l->token_type = CHAR_QUOTE;
	if (l->str[l->i] == CHAR_DQUOTE)
		l->token_type = CHAR_DQUOTE;
	else
		l->token_type = CHAR_GENERAL;
	l->i += 1;
	l->word_len += 1;
}
