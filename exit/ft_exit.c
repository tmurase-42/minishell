/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:54:57 by tmurase           #+#    #+#             */
/*   Updated: 2021/05/07 18:03:09 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool ft_exit(t_command *command_info)
{
	(void)command_info;
	printf("exit:ただexitしてるだけなので処理として正しいかどうかは未検討\n");
	//exit(0);
	return (TRUE);
}
