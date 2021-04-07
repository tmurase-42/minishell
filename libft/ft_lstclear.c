/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 14:56:11 by tmurase           #+#    #+#             */
/*   Updated: 2020/07/08 01:35:42 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*present;
	t_list	*tmp_next;

	present = *lst;
	while (present != NULL)
	{
		tmp_next = present->next;
		del(present->content);
		free(present);
		present = tmp_next;
	}
	*lst = NULL;
}
