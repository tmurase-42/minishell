/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:13:32 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 02:18:58 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_cmd(t_cmd *cmd)
{
	char	*new_str;
	t_token	*token;

	if (!cmd->args || (cmd->args && cmd->args->data == NULL))
		return ;
	token = ft_token_get_first(cmd->args);
	new_str = NULL;
	while (token)
	{
		if ((token->type != CHAR_QUOTE && token->type != CHAR_EMPTY))
		{
			new_str = ft_calloc(sizeof(char *), 1);
			ft_expand_cmd_utils(token, &new_str);
			free(token->data);
			token->data = new_str;
		}
		token = token->next;
	}
	return ;
}
