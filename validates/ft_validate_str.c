/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 23:23:46 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 01:30:20 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_validate_str(char *str)
{
	size_t			i;
	t_token_state	state;

	state = STATE_IN_GENERAL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			if (state == STATE_IN_DQUOTE)
				state = STATE_IN_GENERAL;
			else if (state != STATE_IN_QUOTE)
				state = STATE_IN_DQUOTE;
		}
		if (str[i] == '\'')
		{
			if (state == STATE_IN_QUOTE)
				state = STATE_IN_GENERAL;
			else if (state != STATE_IN_DQUOTE)
				state = STATE_IN_QUOTE;
		}
	}
	if (state != STATE_IN_GENERAL)
		return (FALSE);
	return (TRUE);
}
