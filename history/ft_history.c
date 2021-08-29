/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:32:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/29 12:43:00 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_history()
{
	extern t_mshl_data	*g_mshl_data;
	t_history	*history;

	history = g_mshl_data->histories;
	while(history)
	{
		if (history->next || history->number == 1)
			printf("%5zu  %s\n", history->number, history->data);
		history = history->next;
	}
	return (EXIT_SUCCESS);
}
