/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 23:23:46 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/17 10:08:54 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_validate_str(char *str)
{
	size_t			i;
	t_token_state	state;

	state = STATE_IN_GENERAL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (state == STATE_IN_DQUOTE)
				state = STATE_IN_GENERAL;
			else
				state = STATE_IN_DQUOTE;
		}
		if (str[i] == '\'')
		{
			if (state == STATE_IN_QUOTE)
				state = STATE_IN_GENERAL;
			else
				state = STATE_IN_QUOTE;
		}
		i++;
	}
	if (state != STATE_IN_GENERAL)
		return (FALSE);
	return (TRUE);
}
