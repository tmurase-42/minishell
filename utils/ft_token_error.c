/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:09:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/08/29 11:11:27 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_pipe_error(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	if (ft_strchr(tmp->data, '|') != NULL)
		ft_error("syntax error near unexpected token `|'", NULL, 1);
	while (tmp->next != NULL)
	{
		if (ft_strchr(tmp->data, '|') != NULL && ft_strchr(tmp->next->data, '|') != NULL)
			ft_error("syntax error near unexpected token `|'", NULL, 1);
		tmp = tmp->next;
	}
}

static void	ft_check_redirect_error(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (ft_strchr(tmp->data, '>') != NULL && ft_strchr(tmp->next->data, '>') != NULL)
			ft_error("syntax error", NULL, 258);
		if (ft_strchr(tmp->data, '<') != NULL && ft_strchr(tmp->next->data, '>') != NULL)
			ft_error("syntax error", NULL, 258);
		if (ft_strchr(tmp->data, '>') != NULL && ft_strchr(tmp->next->data, '<') != NULL)
			ft_error("syntax error", NULL, 258);
		tmp = tmp->next;
	}

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

static void	ft_check_expect_let(t_token *tokens)
{

	while (tokens && !ft_check_quot(tokens->data))
	{
		if (ft_isalnum_str(tokens->data) != TRUE)
			ft_error("not expect error", "test", 255);
		tokens = tokens->next;
	}
}


static void	ft_check_unexpect_error(t_token *tokens)
{
	while (tokens->next != NULL)
	{
		//printf("tokens->data = %s\n", tokens->data);
		//printf("tokens->type = %d\n", tokens->type);
		//printf("----------------------------------\n");
		tokens = tokens->next;
	}
	if (tokens->type != CHAR_GENERAL)
		ft_error("unexpect error", "minishell", 0);
}

void	ft_check_token_error(t_token *tokens)
{
	t_token *tmp;

	if (!tokens)
		return ;
	tmp = tokens;
	ft_check_pipe_error(tmp);
	ft_check_redirect_error(tmp);
	ft_check_expect_let(tmp);
	ft_check_unexpect_error(tmp);
}


//memo

// パイプやリダイレクトが最後になっている場合はエラー
// セミコロンを利用した連続コマンド実行もエラーで返す
