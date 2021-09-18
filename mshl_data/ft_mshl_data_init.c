/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mshl_data_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:03:45 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/18 16:04:27 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mshl_data	*ft_mshl_data_init(t_env *envs, char *argv[])
{
	t_mshl_data	*mshl_data;

	mshl_data = malloc(sizeof(t_mshl_data));
	if (!mshl_data)
		return (NULL);
	mshl_data->argc = 0;
	mshl_data->argv = argv;
	mshl_data->envs = envs;
	mshl_data->exit_status = 0;
	mshl_data->pipe_state = WRITE_ONLY;
	mshl_data->interrupted = FALSE;
	mshl_data->command = NULL;
	return (mshl_data);
}
