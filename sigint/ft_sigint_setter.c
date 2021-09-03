/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:31:45 by tdofuku           #+#    #+#             */
/*   Updated: 2021/09/01 23:04:25 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sigint_setter(void (*func)(int))
{
	if (signal(SIGINT, func) == SIG_ERR)
		ft_error("signal SIGINT", EXIT_FAILURE);
	if (signal(SIGQUIT, func) == SIG_ERR)
		ft_error("signal SIGINT", EXIT_FAILURE);
}
