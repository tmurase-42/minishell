/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:09:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/08/29 14:30:58 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	ft_check_pipe_error(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	if (ft_strchr(tmp->data, '|') != NULL)
	{
		ft_error_display("minishell", "syntax erro near unexpected token '|'", 1);
		return (FALSE);
	}
	while (tmp->next != NULL)
	{
		if (ft_strchr(tmp->data, '|') != NULL && ft_strchr(tmp->next->data, '|') != NULL)
		{
			ft_error("minishell", "syntax erro near unexpected token '|'", 1);
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

static t_bool	ft_check_redirect_error(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp->next != NULL)
	{
		if (tmp->type != 0 && tmp->next->type != 0)
		{
			ft_error_display("minishell", "syntax error", 1);
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}


static t_bool ft_isalnum_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool ft_check_quot(char *str)
{
	if (str[0] == CHAR_QUOTE || str[0] == CHAR_DQUOTE)
		return (FALSE);
	return (TRUE);
}

static t_bool	ft_check_expect_let(t_token *tokens)
{

	while (tokens && !ft_check_quot(tokens->data))
	{
		if (ft_isalnum_str(tokens->data) != TRUE)
		{
			ft_error_display("minishell", "not expect error", 1);
			return (FALSE);
		}
		tokens = tokens->next;
	}

	return (TRUE);
}


static t_bool	ft_check_unexpect_error(t_token *tokens)
{
	while (tokens->next != NULL)
		tokens = tokens->next;
	if (tokens->type != 0)
	{
		ft_error_display("minishell", "error: identifier unexpected error", 1);
		return (FALSE);
	}
	return (TRUE);
}

t_bool 	ft_check_token_error(t_token *tokens)
{
	t_token *tmp;

	if (!tokens)
		return (FALSE);
	tmp = tokens;
	if (ft_check_pipe_error(tmp) != TRUE)
		return (FALSE);
	if (ft_check_redirect_error(tmp) != TRUE)
		return (FALSE);
	if (ft_check_expect_let(tmp) != TRUE)
		return (FALSE);
	if (ft_check_unexpect_error(tmp) != TRUE)
		return (FALSE);
	return (TRUE);
}


//memo

// パイプやリダイレクトが最後になっている場合はエラー
// セミコロンを利用した連続コマンド実行もエラーで返す
