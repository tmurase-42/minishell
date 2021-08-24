/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:32:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/24 21:50:20 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_history(t_mshl_data *mshl_data)
{
	t_history	*history;

	history = mshl_data->histories;
	while(history)
	{
		if (history->next || history->number == 1)
			printf("%5zu  %s\n", history->number, history->data);
		history = history->next;
	}
	return (EXIT_SUCCESS);
}
