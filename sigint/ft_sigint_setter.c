/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigint_setter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdofuku <tdofuku@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:31:45 by tdofuku           #+#    #+#             */
/*   Updated: 2021/08/31 14:34:08 by tdofuku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sigint_setter(void (*func)(int))
{
	if (signal(SIGINT, func) == SIG_ERR)
		ft_error("signal SIGINT", "error", 0);
	if (signal(SIGQUIT, func) == SIG_ERR)
		ft_error("signal SIGINT", "error", 0);
}
