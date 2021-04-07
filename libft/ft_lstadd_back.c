/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:42:18 by tmurase           #+#    #+#             */
/*   Updated: 2020/07/08 01:31:57 by tmurase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		new->next = tmp->next;
		tmp->next = new;
	}
}

/*
** 【概要】
** 	連結リストの最後に別のノードを連結させる関数。
** 【処理】
** 	ft_lstlastで連結リストの最後まで移動して、最後のノードのnextの別ノードのアドレスを代入
** 	する。
*/
