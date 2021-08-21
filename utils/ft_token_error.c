/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:09:25 by tmurase           #+#    #+#             */
/*   Updated: 2021/08/03 08:32:07 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_pipe_error(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	if (ft_strchr(tmp->data, '|') != NULL)
		ft_error("syntax error near unexpected token `|'", NULL, 258);
	while (tmp)
	{
		if (ft_strchr(tmp->data, '|') != NULL && ft_strchr(tmp->next->data, '|') != NULL)
			ft_error("syntax error near unexpected token `|'", NULL, 258);
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

static void	ft_check_expect_let(t_token *tokens)
{

	while (tokens)
	{
		if (ft_isalnum_str(tokens->data) != TRUE)
			ft_error("not expect error", "test", 255);
		printf("testaaaaaa|||||\n");
		tokens = tokens->next;
	}
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

}
