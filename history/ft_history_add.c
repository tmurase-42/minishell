/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:32:04 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/24 21:44:05 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// #include<readline/readline.h>
// #include<readline/history.h>


static t_history	*history_create(char *data, size_t number)
{
	t_history	*history;

	history = malloc(sizeof(t_history));
	if (!history)
		ft_error("history", "mallocerror", 1);
	history->prev = NULL;
	history->next = NULL;
	history->data = data;
	history->number = number;
	return (history);
}

static	t_history	*history_get_last(t_history *histories)
{
	t_history	*history;

	if (histories == NULL)
		return (NULL);
	history = histories;
	while(history->next)
		history = history->next;
	return (history);
}

int					ft_history_add(char *line, t_mshl_data *mshl_data)
{
	t_history	*last_history;
	t_history	*history;

	if (line == NULL)
		return (EXIT_FAILURE);
	if (mshl_data->histories == NULL)
	{
		mshl_data->histories = history_create(line, 1);
	}
	else
	{
		last_history = history_get_last(mshl_data->histories);
		history = history_create(line, last_history->number + 1);
		last_history->next = history;
	}
	return (EXIT_SUCCESS);
}
