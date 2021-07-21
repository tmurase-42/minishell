/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:34:08 by tmurase           #+#    #+#             */
/*   Updated: 2021/07/17 18:10:42 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token *create_token(void)
{
	t_token *token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		ft_error("malloc error", "malloc");
	token->data = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_cmd	*ft_cmd_lstnew(void)
{
	t_cmd	*value;

	value = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (value == NULL)
		return (NULL);
	value->args = NULL;
	value->next = NULL;
	value->args = create_token();
	return (value);
}

static t_token *last_token(t_token *token)
{
	t_token *target;

	target = token;
	while (target->next)
		target = target->next;
	return (target);
}

static void add_token(t_token *copy)
{
	t_token *next;
	t_token *last;

	if (!copy)
		ft_error("Not extpected error", "unknown");
	next = create_token();
	last = last_token(copy);
	last->next = next;
	next->prev = last;
}

static t_token *copy_token(t_token *token)
{
	t_token *copy;
	t_token *tmp;

	copy = create_token();
	tmp = create_token();
	copy = tmp;
	while (token)
	{
		tmp->data = ft_strdup(token->data);
		if (token->next == NULL)
			break ;
		if (ft_strncmp(token->next->data, "|", 2) == 0)
			break;
		add_token(tmp);
		token = token->next;
		tmp = tmp->next;
	}
	return (copy);
}

static	t_token *shave_token_until_pipe(t_token *token)
{
	t_token *tmp;

	tmp = create_token();
	while (token->next != NULL)
	{
		//tmp = token->next;
		//free(token->data);
		token = token->next;
		if (ft_strncmp(token->prev->data, "|", 2) == 0)
			break ;
	}

	return (token);
}

int		ft_check_pipe(t_token *token)
{
	t_token *tmp;

	tmp = create_token();
	tmp = token;
	while (tmp)
	{
		if (ft_strncmp(tmp->data, "|", 2) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

t_cmd	*ft_parser(t_token *token, t_cmd *cmd)
{
	t_cmd	*next;
	printf("-------token構造体の値------------\n");
	t_token *test;

	test = create_token();
	test = token;
	while (test)
	{
		printf("token->data  = %s\n", test->data);
	//	if (token->prev != NULL)
	//		printf("token->prev  = %s\n", token->prev->data);
	//	if (token->next != NULL)
	//		printf("token->next  = %s\n", token->next->data);
		test = test->next;
	}
	//引数のtokenが連結リストになっているときにコマンド構造体にコピーする。
	//if (token->next != NULL)
	if (ft_check_pipe(token) == TRUE)
	{
		cmd->args = copy_token(token);
		token = shave_token_until_pipe(token);
		next = ft_cmd_lstnew();
		cmd->next = next;
		ft_parser(token, next);
	}
	else
	{
		cmd->args = copy_token(token);
	}

	//tokenをパイプの次の値まで値を削る。
	//if (token->next != NULL)
	//	ft_parser(token, next);
//	t_cmd	*test;
//	test = ft_cmd_lstnew();
//	test = cmd;
//	while (test->args)
//	{
//		printf("cmd->args = %s\n", test->args->data);
//		test->args = test->args->next;
//	}
	return (cmd);
}