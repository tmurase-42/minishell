/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:23:44 by tmurase           #+#    #+#             */
/*   Updated: 2021/04/01 18:49:18 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*treat_lst;
	t_list	*next_lst;

	if (lst == NULL)
		return (NULL);
	treat_lst = ft_lstnew(f(lst->content));
	if (!treat_lst)
	{
		ft_lstclear(&treat_lst, del);
		return (NULL);
	}
	lst = lst->next;
	while (lst != NULL)
	{
		next_lst = ft_lstnew(f(lst->content));
		if (!next_lst)
		{
			ft_lstclear(&next_lst, del);
			return (NULL);
		}
		ft_lstadd_front(&treat_lst, next_lst);
		lst = lst->next;
	}
	return (treat_lst);
}

/*
** 【概要】
** 	引数の連結リストをf関数で処理した結果を別の連結リストとして返却する関数。
** 【処理】
** 	先頭ノードをlstnewで作成、次ノード以降もlstnewで作成したものをlstadd_frontで連結させて
** 	いく。
*/
